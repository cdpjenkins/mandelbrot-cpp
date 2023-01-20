#include <iostream>
using namespace std;
#include <filesystem>
namespace fs = std::filesystem;


#include <SDL.h>
#include <SDL_image.h>

#include "PngSaver.hpp"
#include "MandelbrotRenderer.hpp"

PngSaver::PngSaver(string & pngs_dir) :
    pngs_dir(pngs_dir)
{
    fs::path base_path(pngs_dir);

    if (!fs::exists(pngs_dir)) {
        fs::create_directory(pngs_dir);
    }
} 

void PngSaver::save_png(RenderedMandelbrot &rendered_mandelbrot) {
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(
        (void*) rendered_mandelbrot.get_buffer(),
        rendered_mandelbrot.width,
        rendered_mandelbrot.height,
        SDL_BITSPERPIXEL(SDL_PIXELFORMAT_RGBA32),
        rendered_mandelbrot.width * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGBA32),
        SDL_PIXELFORMAT_RGBA32
    );

    if (!surface) {
        throw runtime_error("Failed creating new surface: "s + SDL_GetError());
    }

    ostringstream png_name_stream;
    // TODO - could let filesystem library do this for us...
    png_name_stream << pngs_dir << "/mandie_" << png_counter++ << ".png";

    auto png_name = png_name_stream.str();

    cout << "Saving " << png_name << endl;

    int rc = IMG_SavePNG(surface, png_name.c_str());
    if (rc != 0) {
        throw runtime_error("Failed to save PNG: "s + SDL_GetError());
    }
}
