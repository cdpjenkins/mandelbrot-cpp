#ifndef _PNG_SAVER_HPP
#define _PNG_SAVER_HPP

#include "MandelbrotRenderer.hpp"

class PngSaver {
private:
    int png_counter {0};

public:
    void save_png(MandelbrotRenderer &mandie);
};

#endif // _PNG_SAVER_HPP
