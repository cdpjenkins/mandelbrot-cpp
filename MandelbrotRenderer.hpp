#ifndef _MANDELBROTRENDERER_HPP
#define _MANDELBROTRENDERER_HPP

#include <iostream>
using namespace std;

#include "Colour.hpp"
#include "Mandelbrot.hpp"

class MandelbrotRenderer {
public:
    MandelbrotRenderer(int screen_width, int screen_height)
        : mandelbrot(400)
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
    void zoom_in_to(int x, int y);
    void zoom_out_to(int x, int y);

    void increase_depth() {
        mandelbrot.iteration_depth += 10;
        cout << mandelbrot.iteration_depth << endl;
    }

    void decrease_depth() {
        mandelbrot.iteration_depth -= 10;
        cout << mandelbrot.iteration_depth << endl;
    }

    // TODO make this private again and move the memcpy into this class
    Colour *buffer;

private:
    int screen_width;
    int screen_height;
    Complex centre = Complex(0, 0);
    double zoom_size = 4;
    Mandelbrot mandelbrot;

    Complex screen_to_complex(int x, int y) const;
};

#endif // _MANDELBROTRENDERER_HPP
