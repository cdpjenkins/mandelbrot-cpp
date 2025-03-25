#include "Mandelbrot.hpp"

int Mandelbrot::compute(const Complex& k) const {
    // Fast bailout checks for points in the main cardioid or period-2 bulb
    if (k.is_in_main_cardioid() || k.is_in_period2_bulb()) {
        return -1;  // Point is in the set
    }

    Complex z = Complex::ZERO();

    for (int n = 0; n < iteration_depth; n++) {
        z.square_and_add(k);
        if (z.norm() >= 16) {
            return n;
        }
    }

    return -1;
}
