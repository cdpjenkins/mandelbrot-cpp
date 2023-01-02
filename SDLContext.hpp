#ifndef SDL_CONTEXT_HPP
#define SDL_CONTEXT_HPP

#include <vector>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "Config.hpp"
#include "RenderedMandelbrot.hpp"
#include "PngSaver.hpp"


using namespace std;

class SDLTextureWrapper {
public:
    SDLTextureWrapper(SDL_Window *window, SDL_Renderer *renderer, int width, int height) :
        width(width),
        height(height),
        texture(SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height))
    {
        if (texture == nullptr) {
            cout << "SDL_CreateTexture " << " " << SDL_GetError() <<  endl;
        }

    }

    ~SDLTextureWrapper() {
        SDL_DestroyTexture(texture);
    }

    SDL_Texture *texture;
    int width;
    int height;
};

class SDLContext {
public:
    SDLContext(int initial_width, int initial_height);
    ~SDLContext();

    void copy_rendered_mandie_to_screen(RenderedMandelbrot & mandie);
    void resize(int width, int height);
    void send_redraw_event(MandelbrotRenderer& mandelbrot_renderer) const;

private:
    int sdl_init_rc;
    int img_init_rc;
    SDL_Window *window = nullptr;
    SDL_Joystick* joystick = nullptr;
public:
    const uint32_t redraw_event_id;
    SDL_Renderer *renderer;
private:
    // SDL_Texture *mandelbrot_texture;
    unique_ptr<SDLTextureWrapper> mandelbrot_texture;
};

#endif // SDL_CONTEXT_HPP
