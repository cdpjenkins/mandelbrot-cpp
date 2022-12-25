#ifndef SDL_CONTEXT_HPP
#define SDL_CONTEXT_HPP

#include <vector>

#include <SDL.h>

#include "Config.hpp"
#include "MandelbrotRenderer.hpp"
#include "PngSaver.hpp"


using namespace std;

class SDLContext {
public:
    SDLContext();
    ~SDLContext();

    void main_loop();

    SDL_Renderer *renderer = nullptr;

    void copy_rendered_mandie_to_screen(MandelbrotRenderer & mandie);

private:
    SDL_Joystick* joystick = nullptr;
    SDL_Window *window = nullptr;

    SDL_Texture *mandelbrot_texture;
};

#endif // SDL_CONTEXT_HPP
