#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include <string>
using namespace std;

#include "Complex.hpp"

class Config {
public:
    int iteration_depth = 400;
    double zoom_factor = 0.7;
    double max_zoom = 0.000000000000000000001;
    string png_base = "pngs/mandie_"s;
    bool auto_zoom = false;
    Complex zoom_to = Complex(0, 0);
    Complex initial_coords = Complex(0, 0);
    double initial_zoom;

    static Config parse(int argc, char** argv);

};

#endif // _CONFIG_HPP
