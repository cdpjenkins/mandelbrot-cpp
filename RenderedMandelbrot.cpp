//
// Created by Chris Jenkins on 31/12/2022.
//

#include "RenderedMandelbrot.hpp"

RenderedMandelbrot::RenderedMandelbrot(int width, int height) :
        width(width),
        height(height)
{
    buffer = new Colour[width * height];
}

RenderedMandelbrot::~RenderedMandelbrot() {
    delete buffer;
}

