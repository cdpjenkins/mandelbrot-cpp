#include <iostream>

#include <SDL.h>
#include <SDL_error.h>

#include "SDLContext.hpp"

using namespace std;

int main() {
    SDLContext sdl = SDLContext();

    // TODO main_loop really shouldn't be in SDLContext
    sdl.main_loop();
}
