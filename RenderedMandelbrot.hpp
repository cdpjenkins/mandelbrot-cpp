//
// Created by Chris Jenkins on 31/12/2022.
//

#ifndef MANDELBROT_RENDEREDMANDELBROT_HPP
#define MANDELBROT_RENDEREDMANDELBROT_HPP

#include "Colour.hpp"

class RenderedMandelbrot {

public:
    RenderedMandelbrot(int width, int height);

    virtual ~RenderedMandelbrot();

    void set_pixel(int x, int y, Colour && colour) {
        buffer[y * width + x] = colour;
    }

    Colour * get_buffer() {
        return buffer;
    }

    int width;
    int height;

private:
    Colour *buffer;
};

#endif //MANDELBROT_RENDEREDMANDELBROT_HPP
