#ifndef _MANDELBROTRENDERER_HPP
#define _MANDELBROTRENDERER_HPP

#include <iostream>
using namespace std;

#include "Colour.hpp"
#include "Config.hpp"
#include "Mandelbrot.hpp"
#include "RenderedMandelbrot.hpp"

class MandelbrotRenderer {
public:
    MandelbrotRenderer(
        int screen_width,
        int screen_height,
        Config & config,
        Complex centre = Complex(0, 0),
        double zoom_size = 4.0
    ) :
            screen_width(screen_width),
            screen_height(screen_height),
            config(config),
            centre(centre),
            zoom_size(zoom_size),
            rendered_mandelbrot(screen_width, screen_height)
    {}

    void render_to_buffer(Mandelbrot & mandelbrot);
    void zoom_in_to(int x, int y);
    void zoom_in_to(Complex & centre);
    void zoom_out_to(int x, int y);

    // TODO make this private again and move the memcpy into this class

    int screen_width;
    int screen_height;

    double zoom_size = 4;
    Complex centre = Complex(0, 0);

    RenderedMandelbrot rendered_mandelbrot;

private:
    Config config;

    [[nodiscard]]
    Complex screen_to_complex(int x, int y) const;

    double aspect_ratio = (double)screen_height / screen_width;
};

#endif // _MANDELBROTRENDERER_HPP
