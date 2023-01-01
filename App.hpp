#ifndef MANDELBROT_APP_HPP
#define MANDELBROT_APP_HPP

#include <memory>

using namespace std;

#include "Config.hpp"
#include "SDLContext.hpp"

class App {
public:
    explicit App(Config & config);

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

#endif // MANDELBROT_APP_HPP
