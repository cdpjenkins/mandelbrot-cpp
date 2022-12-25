#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_error.h>

#include "App.hpp"
#include "Config.hpp"
#include "SDLContext.hpp"

using namespace std;

int main(int argc, char** argv) {

    Config config = Config::parse(argc, argv);

    App app(config);

    // TODO main_loop really shouldn't be in SDLContext
    app.main_loop();
}
