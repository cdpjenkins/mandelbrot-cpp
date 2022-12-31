#ifndef _PNG_SAVER_HPP
#define _PNG_SAVER_HPP

#include "MandelbrotRenderer.hpp"

class PngSaver {
public:
    PngSaver(string & png_base) :
        png_base(png_base) {} 
    void save_png(RenderedMandelbrot &rendered_mandelbrot);

private:
    int png_counter {0};
    string png_base;
};

#endif // _PNG_SAVER_HPP
