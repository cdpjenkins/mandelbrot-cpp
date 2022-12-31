#ifndef _APP_HPP
#define _APP_HPP

#include <memory>

using namespace std;

#include "Config.hpp"
#include "SDLContext.hpp"

class App {
public:
    App(Config & config) :
        width(config.initial_width),
        height(config.initial_height),
        config(config),
        sdl(config.initial_width, config.initial_height),
        mandelbrot(config.iteration_depth),
        mandelbrot_renderer(make_unique<MandelbrotRenderer>(
                width,
                height,
                config,
                config.initial_coords,
                config.initial_zoom)),
        png_saver(PngSaver(config.png_base))
    {
        // constructor body left intentionally blank
    }

    void main_loop();

private:
    Config config;
    SDLContext sdl;

    int width;
    int height;

    Mandelbrot mandelbrot;
    unique_ptr<MandelbrotRenderer> mandelbrot_renderer;
    PngSaver png_saver;
    void render_mandie();
};

#endif // _APP_HPP
