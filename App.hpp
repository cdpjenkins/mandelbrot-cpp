#ifndef _APP_HPP
#define _APP_HPP

#include <memory>

using namespace std;

#include "Config.hpp"
#include "SDLContext.hpp"

// TODO don't hardcode these forever innit... or maybe call them INITIAL_WIDTH|HEIGHT
const int WIDTH = 1280;
const int HEIGHT = 800;

class App {
public:
    App(Config & config) :
        width(WIDTH),
        height(HEIGHT),
        config(config),
        sdl(SDLContext()),
        mandie(make_unique<MandelbrotRenderer>(WIDTH, HEIGHT, config)),
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

    unique_ptr<MandelbrotRenderer> mandie;
    PngSaver png_saver;
    void render_mandie();
};

#endif // _APP_HPP
