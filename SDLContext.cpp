#include <exception>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "SDLContext.hpp"
#include "MandelbrotRenderer.hpp"

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 800;

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *texture_filename) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, texture_filename);
    if (texture == NULL) {
        throw exception();
    }
    return texture;
}

SDLContext::SDLContext() : mandie(WIDTH, HEIGHT) {

    int rc = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    if (rc != 0) {
        throw exception();
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("Mandelbrot!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    if (window == NULL) {
        throw exception();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    mandelbrot_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    if (mandelbrot_texture == NULL) {
        cout << "SDL_CreateTexture " << rc << " " << SDL_GetError() <<  endl;
    }

    SDL_UpdateWindowSurface(window);
}

SDLContext::~SDLContext() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_JoystickClose( joystick );
    SDL_Quit();
}

void SDLContext::render_mandie() {
    int rc;
    int texture_pitch;
    void *texture_pixels;

    mandie.render_to_buffer();

    if (SDL_LockTexture(mandelbrot_texture, NULL, &texture_pixels, &texture_pitch) != 0) {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
    }
    else {
        memcpy(texture_pixels, mandie.buffer, texture_pitch * HEIGHT);
    }

    SDL_UnlockTexture(mandelbrot_texture);
}

void SDLContext::main_loop() {
    int rc;

    Uint32 start_time;

    render_mandie();

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.scancode == SDL_SCANCODE_Q) {
                        quit = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    cout << "button: " << (int)e.button.button << endl;

                    if (e.button.button == SDL_BUTTON_LEFT) {
                        mandie.zoom_in_to(e.button.x, e.button.y);
                    } else {
                        mandie.zoom_out_to(e.button.x, e.button.y);
                    }

                    render_mandie();

                    break;
            }
        }

        rc = SDL_RenderCopy(renderer, mandelbrot_texture, NULL, NULL);
        if (rc != 0) {
            cout << "SDL_RenderCopy " << rc << " " << SDL_GetError() << " " << mandelbrot_texture << endl;
        }
        SDL_RenderPresent(renderer);
    }
}
