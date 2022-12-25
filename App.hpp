#ifndef _APP_HPP
#define _APP_HPP

#include "Config.hpp"
#include "SDLContext.hpp"

class App {
public:
    App(Config & config, SDLContext & sdl) :
        config(config),
        sdl(sdl)
    {
        // constructor body left intentionally blank
    }

    void main_loop();

private:
    Config config;
    SDLContext sdl;
};

#endif // _APP_HPP
