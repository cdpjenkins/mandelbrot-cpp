#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_error.h>

#include "Config.hpp"
#include "SDLContext.hpp"

using namespace std;

int main(int argc, char** argv) {

    Config config = Config::parse(argc, argv);

    SDLContext sdl = SDLContext(config);

    // TODO main_loop really shouldn't be in SDLContext
    sdl.main_loop();
}
