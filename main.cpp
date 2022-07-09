#include <iostream>

#include <SDL.h>
#include <SDL_error.h>

#include "SDLContext.hpp"

using namespace std;

int main() {
    cout << "Mandelbrot!" << endl;

    SDLContext sdl = SDLContext();

    sdl.main_loop();
}
