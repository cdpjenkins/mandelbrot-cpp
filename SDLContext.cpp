#include <stdexcept>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "SDLContext.hpp"
#include "MandelbrotRenderer.hpp"
#include "PngSaver.hpp"

using namespace std;

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *texture_filename) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, texture_filename);
    if (texture == nullptr) {
        throw runtime_error("Failed to load texture "s + texture_filename);
    }
    return texture;
}

SDLContext::SDLContext(int initial_width, int initial_height) :
    sdl_init_rc(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)),
    img_init_rc(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)),
    window(SDL_CreateWindow("Mandelbrot!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            initial_width, initial_height,
                                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS)),
    renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)),
    mandelbrot_texture(make_unique<SDLTextureWrapper>(window, renderer, initial_width, initial_height)),
    redraw_event_id(SDL_RegisterEvents(1))
{
    // TODO try turning texture, renderer and window into RAII objects so we don't have to manually destroy stuff in destructor

    SDL_UpdateWindowSurface(window);
}

SDLContext::~SDLContext() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_JoystickClose( joystick );
    SDL_Quit();
}

void SDLContext::copy_rendered_mandie_to_screen(MandelbrotRenderer & mandie) {
    int rc;
    int texture_pitch;
    void *texture_pixels;

    // TODO this is going to blow up if mandie has been deleted since we started rendering!
    // Note that this will happen if we resize the window!

    // TODO use RAII to make this a bit less hairy...

    if (SDL_LockTexture(mandelbrot_texture->texture, nullptr, &texture_pixels, &texture_pitch) != 0) {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
    }
    else {
        memcpy(texture_pixels, mandie.rendered_mandelbrot.get_buffer(), texture_pitch * mandie.screen_height);
    }

    SDL_UnlockTexture(mandelbrot_texture->texture);

    SDL_Rect src_rect = { 0, 0, mandie.screen_width, mandie.screen_height };
    SDL_Rect dest_rect = { 0, 0, mandie.screen_width, mandie.screen_height };

    rc = SDL_RenderCopy(renderer, mandelbrot_texture->texture, &src_rect, &dest_rect);
    if (rc != 0) {
        throw runtime_error("SDL_RenderCopy failed with "s + SDL_GetError());
    }
    SDL_RenderPresent(renderer);
}

void SDLContext::resize(int width, int height) {
    mandelbrot_texture.reset(new SDLTextureWrapper(window, renderer, width, height));
}

void SDLContext::send_redraw_event(MandelbrotRenderer &renderer) {
    if (redraw_event_id != ((Uint32)-1)) {
        SDL_Event event;
        memset(&event, 0, sizeof(event));
        event.type = redraw_event_id;
        event.user.code = 0; // TODO call this REDRAW or something
        event.user.data1 = &renderer;
        event.user.data2 = 0;
        SDL_PushEvent(&event);
    }
}
