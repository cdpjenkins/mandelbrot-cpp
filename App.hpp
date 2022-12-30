#ifndef _APP_HPP
#define _APP_HPP

#include <memory>

using namespace std;

#include "Config.hpp"
#include "SDLContext.hpp"

const int INITIAL_WIDTH = 1280;
const int INITIAL_HEIGHT = 800;

class App {
public:
    App(Config & config) :
        width(INITIAL_WIDTH),
        height(INITIAL_HEIGHT),
        config(config),
        sdl(SDLContext()),
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
