#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>

#include "../src/Mandelbrot.hpp"

Mandelbrot mandie{100};

TEST_CASE("Complex number with high magnitude is recognised as not being in the Mandelbrot set") {
    CHECK(mandie.compute(Complex{-20, -20}) == 0);
}

TEST_CASE("Complex number that is within the Mandelbrot set is recognised as being so") {
    CHECK(mandie.compute(Complex{0, 0}) == -1);
}

