#ifndef _MANDELBROT_HPP
#define _MANDELBROT_HPP

#include "Complex.hpp"

class Mandelbrot {
public:
    Mandelbrot(int iteration_depth) {
        this->iteration_depth = iteration_depth;
    }

    int compute(const Complex& k) const;
    int iteration_depth;
};

#endif // _MANDELBROT_HPP
