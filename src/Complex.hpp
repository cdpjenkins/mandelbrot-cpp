#ifndef MANDELBROT_COMPLEX_HPP
#define MANDELBROT_COMPLEX_HPP

#include <sstream>
#include <iostream>
#include <cmath>

using namespace std;

// TODO - turns out there is a complex class in the std library that we could just use...
class Complex {
public:
    double re, im;

    Complex() : re(0), im(0) {}  // Default constructor

    Complex(const double re, const double im) : re(re), im(im) {}

    [[maybe_unused]] [[nodiscard]]
    inline Complex squared() const {
        double re_squared = re * re;
        double im_squared = im * im;
        double re_im = re * im;
        
        return Complex{
            re_squared - im_squared,
            re_im + re_im
        };
    }

    inline void square_and_add(const Complex& k) {
        double re_squared = re * re;
        double im_squared = im * im;
        double re_im = re * im;
        
        re = re_squared - im_squared + k.re;
        im = re_im + re_im + k.im;
    }

    inline Complex operator+(const Complex& that) const {
        return Complex{re + that.re, im + that.im};
    }

    [[nodiscard]]
    inline double norm() const {
        return re*re + im*im;
    }

    // Fast check if point is in the main cardioid or period-2 bulb
    [[nodiscard]]
    inline bool is_in_main_cardioid() const {
        double q = (re - 0.25) * (re - 0.25) + im * im;
        return q * (q + (re - 0.25)) < 0.25 * im * im;
    }

    // Fast check if point is in the period-2 bulb
    [[nodiscard]]
    inline bool is_in_period2_bulb() const {
        return (re + 1.0) * (re + 1.0) + im * im < 0.0625;
    }

    static inline Complex ZERO() {
        return Complex{0, 0};
    }

    static Complex parse(const char *arg);
};

#endif // MANDELBROT_COMPLEX_HPP