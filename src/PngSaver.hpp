#ifndef MANDELBROT_PNG_SAVER_HPP
#define MANDELBROT_PNG_SAVER_HPP

#include <filesystem>
namespace fs = std::filesystem;

#include "MandelbrotRenderer.hpp"

class PngSaver {
public:
    explicit PngSaver(const string& pngs_dir);

    void save_png(RenderedMandelbrot &rendered_mandelbrot);

private:
    int png_counter {0};
    fs::path pngs_dir;
};

#endif // MANDELBROT_PNG_SAVER_HPP
