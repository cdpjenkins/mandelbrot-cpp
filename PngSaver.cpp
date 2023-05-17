#include <iostream>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;


#include <SDL.h>
#include <SDL_image.h>

#include "PngSaver.hpp"
#include "MandelbrotRenderer.hpp"

PngSaver::PngSaver(const string& pngs_dir) :
    pngs_dir(pngs_dir)
{
    fs::path base_path(pngs_dir);

    if (!fs::exists(pngs_dir)) {
        fs::create_directory(pngs_dir);
    }
} 

void PngSaver::save_png(RenderedMandelbrot &rendered_mandelbrot) {
    // TODO consider RAII to create/free the surface
    SDL_Surface* png_surface = SDL_CreateRGBSurfaceWithFormatFrom(
        (void*) rendered_mandelbrot.get_buffer(),
        rendered_mandelbrot.width,
        rendered_mandelbrot.height,
        SDL_BITSPERPIXEL(SDL_PIXELFORMAT_RGBA32),
        rendered_mandelbrot.width * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA32),
        SDL_PIXELFORMAT_RGBA32
    );

    if (!png_surface) {
        throw runtime_error("Failed creating new surface: "s + SDL_GetError());
    }

    // Sadly we can't use std::format() because clang appears not to support it yet
    const string &png_file_name = "mandie_"s + to_string(png_counter++) + ".png";
    fs::path file_path = pngs_dir / png_file_name;

    int rc = IMG_SavePNG(png_surface, file_path.string().c_str());
    if (rc != 0) {
        throw runtime_error("Failed to save PNG: "s + SDL_GetError());
    }

    SDL_FreeSurface(png_surface);
}
