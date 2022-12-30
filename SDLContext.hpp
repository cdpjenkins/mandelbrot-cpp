#ifndef SDL_CONTEXT_HPP
#define SDL_CONTEXT_HPP

#include <vector>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "Config.hpp"
#include "MandelbrotRenderer.hpp"
#include "PngSaver.hpp"


using namespace std;

class SDLTextureWrapper {
public:
    SDLTextureWrapper(SDL_Window *window, SDL_Renderer *renderer, int width, int height) :
        texture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height))
    {
        if (texture == nullptr) {
            cout << "SDL_CreateTexture " << " " << SDL_GetError() <<  endl;
        }

    }

    ~SDLTextureWrapper() {
        cout << "~SDLTextureWrapper" << endl;
        SDL_DestroyTexture(texture);
    }

    SDL_Texture *texture;
};

class SDLContext {
public:
    SDLContext();
    ~SDLContext();

    void main_loop();
    void copy_rendered_mandie_to_screen(MandelbrotRenderer & mandie);
    void resize(int width, int height);

private:
    int sdl_init_rc;
    int img_init_rc;
    SDL_Window *window = nullptr;
    SDL_Joystick* joystick = nullptr;
public:
    SDL_Renderer *renderer;
private:
    // SDL_Texture *mandelbrot_texture;
    unique_ptr<SDLTextureWrapper> mandelbrot_texture;
};

#endif // SDL_CONTEXT_HPP
