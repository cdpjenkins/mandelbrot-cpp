#include <iostream>
using namespace std;

#include <SDL.h>

#include "MandelbrotRenderer.hpp"

const int colour_cycle_period = 120;

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

void MandelbrotRenderer::render_to_buffer() {

    Uint32 start_time = SDL_GetTicks();

    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            // TODO this is probably very inefficient with all the divides and multiplies
            Complex k = screen_to_complex(x, y);

            int n = mandelbrot.compute(k);

            // TODO iteration depth is basically hardcoded here (100)
            double brightness = n != -1
                    ? (double)n / mandelbrot.iteration_depth * 0xFF
                    : 0xFF;

            buffer[y * screen_width + x] = iterations_to_rgb(n);
        }
    }

    cout << SDL_GetTicks() - start_time << "ms" <<endl;
}

Complex MandelbrotRenderer::screen_to_complex(int x, int y) {
    double x_progress = (double)x / screen_width;
    double y_progress = (double)y / screen_height;

    Complex top_left = Complex(centre.re - zoom_size, centre.im - zoom_size);
    Complex bottom_right = Complex(centre.re + zoom_size, centre.im + zoom_size);

    double complex_width = zoom_size * 2;
    double complex_height = zoom_size * 2;

    double re = top_left.re + complex_width * x_progress;
    double im = top_left.im + complex_height * y_progress;

    return Complex(re, im);
}

void MandelbrotRenderer::zoom_in_to(int x, int y) {
    centre = screen_to_complex(x, y);
    zoom_size *= 0.7;
    render_to_buffer();
}

void MandelbrotRenderer::zoom_out_to(int x, int y) {
    centre = screen_to_complex(x, y);
    zoom_size /= 0.7;
    render_to_buffer();
}
