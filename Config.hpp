#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include <string>

using namespace std;

class Config {
public:
    int iteration_depth = 400;
    double zoom_factor = 0.7;
    double max_zoom = 0.000000000000000000001;
    string png_base = "pngs/mandie_"s;
    bool auto_zoom = false;
};

#endif // _CONFIG_HPP
