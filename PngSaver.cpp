#include <iostream>
#include <sstream>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

// #include <stdio>
// using namespace std;

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

    ostringstream png_name;
    png_name << "pngs/mandie_" << png_counter++ << ".png";

    cout << "saving " << png_name.str() << endl;
    int rc = IMG_SavePNG(surface, png_name.str().c_str());
    if (rc != 0) {
        throw runtime_error("Failed to save PNG: "s + SDL_GetError());
    }
}
