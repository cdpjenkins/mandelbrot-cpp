#include <iostream>
using namespace std;

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
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            float im = (float)(y - screen_height/2) * 4 / screen_height;
            float re = (float)(x - screen_width/2) * 4 / screen_width;

            Complex k = Complex(re, im);

            int n = mandelbrot.compute(k);

            // TODO iteration depth is basically hardcoded here (100)
            float brightness = n != -1
                    ? (float)n / mandelbrot.iteration_depth * 0xFF
                    : 0xFF;

            buffer[y * screen_width + x] = iterations_to_rgb(n);
            // buffer[y * screen_width + x] = Colour(brightness, brightness, brightness, 0xFF);
        }
    }
}
