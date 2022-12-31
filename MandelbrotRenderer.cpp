#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
using namespace std;

#include <SDL.h>

#include "MandelbrotRenderer.hpp"

const int colour_cycle_period = 256;

Colour iterations_to_rgb(int iterations) {
    // This is kind of like doing HSV to RGB conversation, except:
    // thankfully we don't have to do *full* HSV->RGB conversation because
    // saturation and value are always full

    if (iterations == -1) {
        return Colour(0, 0, 0, 0xFF);
    }

    int segment_size = colour_cycle_period / 6;
    int segment = (iterations / segment_size) % 6;
    int pos_in_segment = iterations % segment_size;
    int segment_progress = (pos_in_segment * 255) / segment_size;

    switch (segment) {
        case 0:
            return Colour(255, segment_progress, 0, 255);
            break;
        case 1:
            return Colour(255 - segment_progress, 255, 0, 255);
            break;
        case 2:
            return Colour(0, 255, segment_progress, 255);
            break;
        case 3:
            return Colour(0, 255 - segment_progress, 255, 255);
            break;
        case 4:
            return Colour(segment_progress, 0, 255, 255);
            break;
        case 5:
            return Colour(255, 0, 255 - segment_progress, 255);
            break;
        default:
            // we can never get here, but if we do...
            return Colour(255, 255, 255, 255);
    }
}

void MandelbrotRenderer::render_to_buffer(Mandelbrot & mandelbrot) {
    Uint32 start_time = SDL_GetTicks();

    vector<thread> render_threads;

    const auto processor_count = std::thread::hardware_concurrency();
    cout << "num cpu cores: " << processor_count << endl;

    int num_threads = max((const unsigned int)10, processor_count);
    int slice_size = screen_height / num_threads;

    for (auto y_slice = 0; y_slice < screen_height; y_slice += slice_size) {

        auto render_lambda = [y_slice , this, &mandelbrot, slice_size] {
            for (auto y = y_slice; y < y_slice + slice_size && y < screen_height; y++) {
                for (auto x = 0; x < screen_width; x++) {
                    // this is probably very inefficient with all the divides and multiplies
                    Complex k = screen_to_complex(x, y);

                    int n = mandelbrot.compute(k);

                    rendered_mandelbrot.set_pixel(x, y, iterations_to_rgb(n));
                }
            }
        };

        render_threads.emplace_back(render_lambda);
    }

    std::for_each(render_threads.begin(), render_threads.end(), [](thread& t){ t.join(); } );

    cout << "rendering took " << SDL_GetTicks() - start_time << "ms" <<endl;
}

Complex MandelbrotRenderer::screen_to_complex(const int x, const int y) const {
    double x_progress = (double)x / screen_width;
    double y_progress = (double)y / screen_height;

    Complex top_left{centre.re - zoom_size, centre.im - zoom_size*aspect_ratio};

    double complex_width = zoom_size * 2;
    double complex_height = zoom_size * 2 * aspect_ratio;

    double re = top_left.re + complex_width * x_progress;
    double im = top_left.im + complex_height * y_progress;

    return Complex(re, im);
}

void MandelbrotRenderer::zoom_in_to(const int x, const int y) {
    centre = screen_to_complex(x, y);

    zoom_in_to(centre);
}

void MandelbrotRenderer::zoom_in_to(Complex & centre) {
    zoom_size *= config.zoom_factor;
    this->centre = centre;
    cout << setprecision(30) << centre.re << " + " << centre.im << "i" << " " << zoom_size << endl;
}

void MandelbrotRenderer::zoom_out_to(const int x, const int y) {
    centre = screen_to_complex(x, y);
    zoom_size /= config.zoom_factor;
    cout << x << ", " << y << endl;
}
