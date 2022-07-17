#ifndef _MANDELBROTRENDERER_HPP
#define _MANDELBROTRENDERER_HPP

#include "Colour.hpp"
#include "Mandelbrot.hpp"

class MandelbrotRenderer {
public:
    MandelbrotRenderer(int screen_width, int screen_height)
        : mandelbrot(200)
    {
        this->screen_width = screen_width;
        this->screen_height = screen_height;

        buffer = new Colour[screen_width * screen_height];
    }

    ~MandelbrotRenderer()
    {
        delete buffer;
    }

    inline Colour colour_at(int x, int y) {
        return buffer[y * screen_width + x];
    }

    void render_to_buffer();

private:
    int screen_width;
    int screen_height;

    // TODO this should be some STL type that I don't know about yet
    Colour *buffer;

    Mandelbrot mandelbrot;
};

#endif // _MANDELBROTRENDERER_HPP
