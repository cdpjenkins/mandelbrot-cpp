#include <iostream>
#include <sstream>

#include "Config.hpp"

Config Config::parse(int argc, char** argv) {
    Config config;

    for (int i = 0; i < argc; i++) {
        string arg_key {argv[i]};

        cout << arg_key << endl;

        if (arg_key == "--iteration-depth") {
            config.iteration_depth = stoi(argv[++i]);
        } else if (arg_key == "--zoom-factor") {
            config.zoom_factor = stod(argv[++i]);
        } else if (arg_key == "--max-zoom") {
            config.max_zoom = stod(argv[++i]);
        } else if (arg_key == "--png-base") {
            config.png_base = argv[++i];
        } else if (arg_key == "--auto-zoom-to") {
            config.auto_zoom = true;

            // TODO move this "lovely" parsing code maybe into Complex class
            istringstream coords_stringstream(argv[++i]);
            string re_string;
            string im_string;
            getline(coords_stringstream, re_string, ',');
            getline(coords_stringstream, im_string, ',');
            config.zoom_to = Complex(stod(re_string), stod(im_string));
        }
    }

    return config;
}
