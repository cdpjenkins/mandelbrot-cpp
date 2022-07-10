#ifndef _MANDELBROT_HPP
#define _MANDELBROT_HPP

#include "Complex.hpp"

class Mandelbrot {
public:
    Mandelbrot() {}

    int compute(Complex& k);
};

#endif // _MANDELBROT_HPP
