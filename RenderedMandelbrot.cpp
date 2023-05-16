#include "RenderedMandelbrot.hpp"

RenderedMandelbrot::RenderedMandelbrot(const int width, const int height) :
        width(width),
        height(height)
{
    buffer.reserve(width*height);
}
