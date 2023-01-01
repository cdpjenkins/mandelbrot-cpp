#ifndef MANDELBROT_SDLAPP_HPP
#define MANDELBROT_SDLAPP_HPP

#include <memory>

using namespace std;

#include "Config.hpp"
#include "SDLContext.hpp"

class SDLApp {
public:
    explicit SDLApp(Config & config);

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

#endif // MANDELBROT_SDLAPP_HPP
