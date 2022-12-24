#include <iostream>
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

    // TODO - pretty sure there's a C++ thing we could use here that would be preferrable
    char png_name[100];
    snprintf(png_name, sizeof(png_name), "pngs/mandie_%05d.png", png_counter++);

    cout << "saving " << png_name << endl;
    int rc = IMG_SavePNG(surface, png_name);
    if (!rc) {
        // throw runtime_error("Failed to save PNG:"s + SDL_GetError());

        cout << rc << " " << SDL_GetError() << endl;
    }
}
