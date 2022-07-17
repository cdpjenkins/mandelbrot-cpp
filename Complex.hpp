#ifndef _COMPLEX_HPP
#define _COMPLEX_HPP

#include "math.h"

// TODO - turns out there is a complex class in the std library that we could just use...
class Complex {
public:
    double re, im;

    Complex(double re, double im) {
        this->re = re;
        this->im = im;
    }

    inline Complex squared() {
        double new_re = re*re - im*im;
        double new_im = re * im * 2;

        return Complex(new_re, new_im);
    }

    inline void square_and_add(Complex k) {
        double new_re = re*re - im*im + k.re;
        double new_im = re * im * 2 + k.im;

        re = new_re;
        im = new_im;
    }

    inline Complex operator+(Complex& that) {
        return Complex(this->re + that.re, this->im + that.im);
    }

    inline double norm() {
        return re*re + im*im;
    }

    static inline Complex ZERO() {
        return Complex(0, 0);
    }
};


#endif // _COMPLEX_HPP