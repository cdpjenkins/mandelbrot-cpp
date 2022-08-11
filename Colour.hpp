#ifndef _COLOUR_HPP
#define _COLOUR_HPP

#include <stdint.h>

class Colour {
public:
    uint8_t r, g, b, a;

    inline Colour() : Colour(0, 0, 0, 0xFF) {}

    inline Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
            r {r},
            g {g},
            b {b},
            a {a} {}
};

#endif // _COLOUR_HPP
