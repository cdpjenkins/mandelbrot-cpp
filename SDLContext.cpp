#include <exception>
#include <iostream>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>

#include "SDLContext.hpp"
#include "Complex.hpp"

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

SDLContext::SDLContext() {
    int rc = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    if (rc != 0) {
        throw exception();
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("MAndelbrot!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    if (window == NULL) {
        throw exception();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_UpdateWindowSurface(window);
}

SDLContext::~SDLContext() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_JoystickClose( joystick );
    SDL_Quit();
}

void SDLContext::main_loop() {
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
            }
        }

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                float im = (float)(y - HEIGHT/2) * 4 / HEIGHT;
                float re = (float)(x - WIDTH/2) * 4 / WIDTH;

                float brightness = sqrtf(re*re + im*im) * 0xFF;
                if (brightness > 0xFF) {
                    brightness = 0xFF;
                }

                Complex z = Complex::ZERO();
                Complex k = Complex(re, im);
                int n;
                for (n = 0; n < 100 && z.modulus() < 4; n++) {
                    z = z.squared() + k;
                }

                brightness = (float)n / 100 * 0xFF;


                SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 0xFF);

                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);
    }
}
