#include <math.h>

#include "Mandelbrot.hpp"

int Mandelbrot::compute(Complex& k) {
    Complex z = Complex::ZERO();

    for (int n = 0; n < iteration_depth; n++) {
        z = z.squared() + k;
        if (z.modulus() >= 4) {
            return n;
        }
    }

    return -1;
}
