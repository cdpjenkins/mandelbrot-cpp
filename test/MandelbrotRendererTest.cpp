#include "doctest.h"

#include <iostream>

#include "../src/MandelbrotRenderer.hpp"

TEST_CASE("Colour of n==0 pixel is red") {
    const Colour colour = iterations_to_rgb(0);

    CHECK(colour.r == 0xFF);
    CHECK(colour.g == 0x00);
    CHECK(colour.b == 0x00);
    CHECK(colour.a == 0xFF);
}

// TODO - this fails in a Release build (presumably when -O3 is turned on but not certain yet) and colours the pixel
// a slightly blue colour. Not sure why yet.
TEST_CASE("Colour of n==0 pixel is red-ish when using weird trig to map iterations to colour") {
    const Colour colour = iterations_to_rgb_using_trig(0);

    CHECK(colour.r == 0x7F);
    CHECK(colour.g == 0x25);
    CHECK(colour.b == 0x00);
    CHECK(colour.a == 0xFF);
}
