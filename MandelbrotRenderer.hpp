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
    );

    void render_to_buffer(Mandelbrot & mandelbrot);
    void zoom_in_to(int x, int y);
    void zoom_in_to(Complex & centre);
    void zoom_out_to(int x, int y);

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

    int num_threads;

    static int get_num_threads(int max_threads = 10);
};

#endif // _MANDELBROTRENDERER_HPP
