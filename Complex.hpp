#ifndef _COMPLEX_HPP
#define _COMPLEX_HPP

class Complex;

class Complex {
public:
    float re, im;

    Complex(float re, float im) {
        this->re = re;
        this->im = im;
    }

    inline Complex squared() {
        float new_re = re*re - im*im;
        float new_im = re * im * 2;

        return Complex(new_re, new_im);
    }

    inline Complex operator+(Complex& that) {
        return Complex(this->re + that.re, this->im + that.im);
    }

    inline float modulus() {
        return sqrtf(re*re + im*im);
    }

    static inline Complex ZERO() {
        return Complex(0, 0);
    }
};


#endif // _COMPLEX_HPP