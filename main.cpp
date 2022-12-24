#include <iostream>
#include <iterator>
#include <string>


#include <SDL.h>
#include <SDL_error.h>

#include "Config.hpp"
#include "SDLContext.hpp"

using namespace std;

int main(int argc, char** argv) {

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
        } else if (arg_key == "--auto-zoom") {
            config.auto_zoom = true;
        }
    }

    SDLContext sdl = SDLContext(config);

    // TODO main_loop really shouldn't be in SDLContext
    sdl.main_loop();
}
