#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_error.h>

#include "App.hpp"
#include "Config.hpp"
#include "SDLContext.hpp"

using namespace std;

int main(int argc, char** argv) {

    // Need to figure out move constructors before these can be moved into initialiser list.
    // Basically, both need to remain in scope or the destructor will cause SDL to be shut
    // down, texture deleted etc, before the program has a chance to run. :-/
    Config config = Config::parse(argc, argv);
    SDLContext sdl = SDLContext();

    App app(config, sdl);

    // TODO main_loop really shouldn't be in SDLContext
    app.main_loop();
}
