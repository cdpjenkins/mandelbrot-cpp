#include <stdexcept>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "SDLContext.hpp"
#include "MandelbrotRenderer.hpp"
#include "PngSaver.hpp"

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 800;

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *texture_filename) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, texture_filename);
    if (texture == nullptr) {
        throw runtime_error("Failed to load texture "s + texture_filename);
    }
    return texture;
}

SDLContext::SDLContext(Config & config) :
        config(config),
        mandie(WIDTH, HEIGHT, config),
        png_saver(PngSaver(config.png_base)) {

    int rc = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
    if (rc != 0) {
        throw runtime_error("SDL_Init failed");
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("Mandelbrot!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        WIDTH, HEIGHT,
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
    if (window == nullptr) {
        throw runtime_error("Failed to create SDL_Window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    mandelbrot_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    if (mandelbrot_texture == nullptr) {
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

    // TODO - really want to do this on a separate thread so the GUI doesn't freeze
    // whilst it's happening
    mandie.render_to_buffer();

    png_saver.save_png(mandie);

    if (SDL_LockTexture(mandelbrot_texture, nullptr, &texture_pixels, &texture_pitch) != 0) {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
    }
    else {
        memcpy(texture_pixels, mandie.buffer, texture_pitch * HEIGHT);
    }

    SDL_UnlockTexture(mandelbrot_texture);

    rc = SDL_RenderCopy(renderer, mandelbrot_texture, nullptr, nullptr);
    if (rc != 0) {
        throw runtime_error("SDL_RenderCopy failed with "s + SDL_GetError());
    }
    SDL_RenderPresent(renderer);
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
                    switch (e.key.keysym.scancode) {
                        case SDL_SCANCODE_Q:
                            quit = true;
                            break;
                        case SDL_SCANCODE_P:
                            cout << "increase depth" << endl;
                            mandie.increase_depth();
                            render_mandie();
                            break;
                        case SDL_SCANCODE_L:
                            cout << "decrease depth" << endl;
                            mandie.decrease_depth();
                            render_mandie();
                            break;
                        case SDL_SCANCODE_KP_ENTER:
                            render_mandie();
                            break;
                        default:
                            // meh, don't care about other keys
                            break;
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

        if (config.auto_zoom) {
            mandie.zoom_in_to(Complex(-1.25721, 0.379069));
            render_mandie();

            if (mandie.zoom_size < config.max_zoom) {
                break;
            }
        }
    }
}
