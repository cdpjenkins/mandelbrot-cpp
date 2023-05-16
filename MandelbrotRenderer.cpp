#include <iostream>
#include <iomanip>
#include <vector>
#include <future>
#include <cmath>
using namespace std;

#include <SDL.h>

#include "MandelbrotRenderer.hpp"

const int colour_cycle_period = 256;

MandelbrotRenderer::MandelbrotRenderer(int screen_width,
                                       int screen_height,
                                       const Config &config,
                                       Complex centre,
                                       double zoom_size) :
        screen_width(screen_width),
        screen_height(screen_height),
        config(config),
        centre(centre),
        zoom_size(zoom_size),
        rendered_mandelbrot(screen_width, screen_height),
        num_threads(get_num_threads(config.max_threads))
{}


Colour iterations_to_rgb(int iterations) {
    // This is kind of like doing HSV to RGB conversation, except:
    // thankfully we don't have to do *full* HSV->RGB conversation because
    // saturation and value are always full

    if (iterations == -1) {
        return Colour{0, 0, 0, 0xFF};
    }

    int segment_size = colour_cycle_period / 6;
    int segment = (iterations / segment_size) % 6;
    int pos_in_segment = iterations % segment_size;
    uint8_t segment_progress = (pos_in_segment * 255) / segment_size;
    uint8_t inverse_segment_progress = 255 - segment_progress;

    switch (segment) {
        case 0:
            return Colour{255, segment_progress, 0, 255};
        case 1:
            return Colour{inverse_segment_progress, 255, 0, 255};
        case 2:
            return Colour{0, 255, segment_progress, 255};
        case 3:
            return Colour{0, inverse_segment_progress, 255, 255};
        case 4:
            return Colour{segment_progress, 0, 255, 255};
        case 5:
            return Colour{255, 0, inverse_segment_progress, 255};
        default:
            // we can never get here, but if we do...
            return Colour{255, 255, 255, 255};
    }
}

Colour iterations_to_rgb_using_trig(int iterations) {
    if (iterations == -1) {
        return Colour{0, 0, 0, 0xFF};
    }

    double theta = 2 * M_PI * iterations / colour_cycle_period;

    uint8_t r = uint8_t(sin(theta) * 128 + 127);
    uint8_t g = uint8_t(sin(theta - M_PI_4) * 128 + 127);
    uint8_t b = uint8_t(sin(theta - M_PI_2) * 128 + 127);

    return Colour{r, g, b, 0xFF};
}

void MandelbrotRenderer::render_to_buffer(Mandelbrot& mandelbrot) {
    Uint32 start_time = SDL_GetTicks();

    vector<future<void>> render_threads;

    int slice_size = screen_height / num_threads;

    for (auto y_slice = 0; y_slice < screen_height; y_slice += slice_size) {
        auto render_lambda = [y_slice , this, &mandelbrot, slice_size] {
            for (auto y = y_slice; y < y_slice + slice_size && y < screen_height; y++) {
                for (auto x = 0; x < screen_width; x++) {
                    // this is probably very inefficient with all the divides and multiplies
                    Complex k = screen_to_complex(x, y);

                    int n = mandelbrot.compute(k);

                    rendered_mandelbrot.set_pixel(x, y, iterations_to_rgb_using_trig(n));
                }
            }
        };

        render_threads.push_back(std::async(std::launch::async, render_lambda));
    }

    std::for_each(render_threads.begin(),
                  render_threads.end(),
                  [](auto & render_future){ render_future.wait(); });

    cout << "rendering took " << SDL_GetTicks() - start_time << "ms" <<endl;
}

int MandelbrotRenderer::get_num_threads(int max_threads) {
    const int processor_count = int(thread::hardware_concurrency());
    const auto num_threads = min(max_threads, processor_count);

    cout << "Using " << num_threads << " rendering threads" << endl;

    return num_threads;
}

Complex MandelbrotRenderer::screen_to_complex(const int x, const int y) const {
    double x_progress = (double)x / screen_width;
    double y_progress = (double)y / screen_height;

    Complex top_left{centre.re - zoom_size, centre.im - zoom_size*aspect_ratio};

    double complex_width = zoom_size * 2;
    double complex_height = zoom_size * 2 * aspect_ratio;

    double re = top_left.re + complex_width * x_progress;
    double im = top_left.im + complex_height * y_progress;

    return Complex{re, im};
}

void MandelbrotRenderer::zoom_in_to(const int x, const int y) {
    centre = screen_to_complex(x, y);

    zoom_in_to(centre);
}

void MandelbrotRenderer::zoom_in_to(Complex &coords) {
    zoom_size *= config.zoom_factor;
    this->centre = coords;
    cout << setprecision(30) << coords.re << " + " << coords.im << "i" << " " << zoom_size << endl;
}

void MandelbrotRenderer::zoom_out_to(const int x, const int y) {
    centre = screen_to_complex(x, y);
    zoom_size /= config.zoom_factor;
    cout << x << ", " << y << endl;
}

void MandelbrotRenderer::scroll(int dx, int dy) {
    centre = centre + Complex(dx * 8 * zoom_size / screen_width, -dy * 8 * zoom_size / screen_height);
}
