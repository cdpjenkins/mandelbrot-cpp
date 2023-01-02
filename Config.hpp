#ifndef MANDELBROT_CONFIG_HPP
#define MANDELBROT_CONFIG_HPP

#include <string>
using namespace std;

#include "Complex.hpp"

class Config {
public:
    int iteration_depth = 800;
    double zoom_factor = 0.7;
    double max_zoom = 0.000000000000000000001;
    string png_base = "pngs/mandie_"s;
    bool auto_zoom = false;
    Complex zoom_to = Complex(0, 0);
    Complex initial_coords = Complex(0, 0);
    double initial_zoom = 4.0;

    static Config parse(int argc, char** argv);

    int initial_width = 1280;
    int initial_height = 800;
    int max_threads;
};

#endif // MANDELBROT_CONFIG_HPP
