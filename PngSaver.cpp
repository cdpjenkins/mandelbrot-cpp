#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>


#include "PngSaver.hpp"
#include "MandelbrotRenderer.hpp"

void PngSaver::save_png(MandelbrotRenderer &mandie) {
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(
        (void*)mandie.buffer,
        mandie.screen_width,
        mandie.screen_height,
        SDL_BITSPERPIXEL(SDL_PIXELFORMAT_RGBA32),
        mandie.screen_width * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA32),
        SDL_PIXELFORMAT_RGBA32
    );

    if (!surface) {
        throw runtime_error("Failed creating new surface: "s + SDL_GetError());
    }

    int rc = IMG_SavePNG(surface, "mandie.png");
    if (!rc) {
        // throw runtime_error("Failed to save PNG:"s + SDL_GetError());

        cout << rc << " " << SDL_GetError() << endl;
    }
}