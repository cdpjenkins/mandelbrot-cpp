#include "RenderedMandelbrot.hpp"

RenderedMandelbrot::RenderedMandelbrot(int width, int height) :
        width(width),
        height(height)
{
    buffer.reserve(width*height);
}
