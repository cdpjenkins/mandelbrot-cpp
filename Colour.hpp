#ifndef MANDELBROT_COLOUR_HPP
#define MANDELBROT_COLOUR_HPP

#include <cstdint>
using namespace std;

class Colour {
public:
    [[maybe_unused]]
    uint8_t r, g, b, a;

    inline Colour() : Colour(0, 0, 0, 0xFF) {}

    inline Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
            r {r},
            g {g},
            b {b},
            a {a} {}
};

#endif // MANDELBROT_COLOUR_HPP
