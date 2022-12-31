//
// Created by Chris Jenkins on 31/12/2022.
//

#ifndef MANDELBROT_RENDEREDMANDELBROT_HPP
#define MANDELBROT_RENDEREDMANDELBROT_HPP

#include <vector>

#include "Colour.hpp"

class RenderedMandelbrot {

public:
    RenderedMandelbrot(int width, int height);

    void set_pixel(int x, int y, Colour && colour) {
        buffer[y * width + x] = colour;
    }

    Colour * get_buffer() {
        return buffer.data();
    }

    int width;
    int height;

private:
    std::vector<Colour> buffer;
};

#endif //MANDELBROT_RENDEREDMANDELBROT_HPP
