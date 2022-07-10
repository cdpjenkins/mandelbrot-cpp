#include <iostream>
using namespace std;

#include "MandelbrotRenderer.hpp"

void MandelbrotRenderer::render_to_buffer() {
    for (int y = 0; y < screen_height; y++) {
        for (int x = 0; x < screen_width; x++) {
            float im = (float)(y - screen_height/2) * 4 / screen_height;
            float re = (float)(x - screen_width/2) * 4 / screen_width;

            Complex k = Complex(re, im);

            int n = mandelbrot.compute(k);

            // TODO iteration depth is basically hardcoded here (100)
            float brightness = n != -1
                    ? (float)n / 100 * 0xFF
                    : 0xFF;

            buffer[y * screen_width + x] = Colour(brightness, brightness, brightness, 0xFF);
        }
    }
}
