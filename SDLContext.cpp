#include <stdexcept>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "SDLContext.hpp"
#include "MandelbrotRenderer.hpp"
#include "PngSaver.hpp"

using namespace std;

const int INITIAL_WIDTH = 1280;
const int INITIAL_HEIGHT = 800;

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *texture_filename) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, texture_filename);
    if (texture == nullptr) {
        throw runtime_error("Failed to load texture "s + texture_filename);
    }
    return texture;
}

SDLContext::SDLContext() :
    sdl_init_rc(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)),
    img_init_rc(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)),
    window(SDL_CreateWindow("Mandelbrot!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        INITIAL_WIDTH, INITIAL_HEIGHT,
                                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS)),
    renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)),
    mandelbrot_texture(make_unique<SDLTextureWrapper>(window, renderer, INITIAL_WIDTH, INITIAL_HEIGHT))
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

    // TODO use RAII to make this a bit less hairy...

    if (SDL_LockTexture(mandelbrot_texture->texture, nullptr, &texture_pixels, &texture_pitch) != 0) {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
    }
    else {

        cout << "texture_pitch: " << texture_pitch << endl;
        cout << "mandie.screen_width: " << mandie.screen_width << endl;   
        cout << "mandie.screen_height: " << mandie.screen_height << endl;   

        memcpy(texture_pixels, mandie.buffer, texture_pitch * mandie.screen_height);
    }

    SDL_UnlockTexture(mandelbrot_texture->texture);

    cout << "about to copy thar texture. renderer: " << renderer << endl;

    SDL_Rect src_rect = { 0, 0, mandie.screen_width, mandie.screen_height };
    SDL_Rect dest_rect = { 0, 0, mandie.screen_width, mandie.screen_height };

    rc = SDL_RenderCopy(renderer, mandelbrot_texture->texture, &src_rect, &dest_rect);
    if (rc != 0) {
        throw runtime_error("SDL_RenderCopy failed with "s + SDL_GetError());
    }
    SDL_RenderPresent(renderer);
}

void SDLContext::main_loop() {
    cout << "lalalala do not call me" <<endl;
}

void SDLContext::resize(int width, int height) {
    mandelbrot_texture.reset(new SDLTextureWrapper(window, renderer, width, height));
}
