#ifndef SDL_CONTEXT_HPP
#define SDL_CONTEXT_HPP

#include <vector>

#include <SDL.h>

#include "MandelbrotRenderer.hpp"

using namespace std;

class SDLContext {
public:
    SDLContext();
    ~SDLContext();

    void main_loop();

    SDL_Renderer *renderer = nullptr;

private:
    SDL_Joystick* joystick = nullptr;
    SDL_Window *window = nullptr;

    SDL_Texture *mandelbrot_texture;

    MandelbrotRenderer mandie;

    void render_mandie();
};

#endif // SDL_CONTEXT_HPP
