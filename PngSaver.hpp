#ifndef _PNG_SAVER_HPP
#define _PNG_SAVER_HPP

#include "MandelbrotRenderer.hpp"

class PngSaver {
public:
    void save_png(MandelbrotRenderer &mandie);
};

#endif // _PNG_SAVER_HPP
