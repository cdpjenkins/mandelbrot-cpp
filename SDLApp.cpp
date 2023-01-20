#include "SDLApp.hpp"

#include <memory>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    Config config = Config::parse(argc, argv);    

    SDLApp app(config);
    app.main_loop();
}

SDLApp::SDLApp(Config &config) :
        width(config.initial_width),
        height(config.initial_height),
        config(config),
        sdl(config.initial_width, config.initial_height),
        mandelbrot(config.iteration_depth),
        mandelbrot_renderer(make_unique<MandelbrotRenderer>(
                width,
                height,
                config,
                config.initial_coords,
                config.initial_zoom)),
        png_saver(PngSaver(config.pngs_dir))
{
    // constructor body left intentionally blank
}

void SDLApp::main_loop() {
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
                            mandelbrot.iteration_depth += 10;
                            cout << mandelbrot.iteration_depth << endl;
                            render_mandie();
                            break;
                        case SDL_SCANCODE_L:
                            cout << "decrease depth" << endl;
                            mandelbrot.iteration_depth -= 10;
                            cout << mandelbrot.iteration_depth << endl;
                            render_mandie();
                            break;
                        case SDL_SCANCODE_KP_ENTER:
                            render_mandie();
                            break;
                        case SDL_SCANCODE_R:
                            sdl.resize(width, height);
                            break;
                        default:
                            // meh, don't care about other keys
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT) {
                        mandelbrot_renderer->zoom_in_to(e.button.x, e.button.y);
                    } else {
                        mandelbrot_renderer->zoom_out_to(e.button.x, e.button.y);
                    }

                    render_mandie();

                    break;
                case SDL_WINDOWEVENT:
                    switch (e.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            width = e.window.data1;
                            height = e.window.data2;
                            cout << "resized: " << e.window.windowID << " " << width << ", " << height << endl;
                            sdl.resize(width, height);
                            mandelbrot_renderer = std::make_unique<MandelbrotRenderer>(
                                width, height, config, mandelbrot_renderer->centre, mandelbrot_renderer->zoom_size);
                            render_mandie();
                            break;
                    }
                    break;
                case SDL_MOUSEWHEEL:
                    mandelbrot_renderer->scroll(e.wheel.x, e.wheel.y);
                    render_mandie();
                    break;
            }

            // Grrr can't handle this in the switch statement because the event_id is not constant.
            if (e.type == sdl.redraw_event_id) {
                sdl.copy_rendered_mandie_to_screen(mandelbrot_renderer->rendered_mandelbrot);
            }
        }

        if (config.auto_zoom) {
            mandelbrot_renderer->zoom_in_to(config.zoom_to);
            render_mandie();

            if (mandelbrot_renderer->zoom_size < config.max_zoom) {
                break;
            }
        }
    }
}

void SDLApp::render_mandie() {
    mandelbrot_renderer->render_to_buffer(mandelbrot);
    png_saver.save_png(mandelbrot_renderer->rendered_mandelbrot);
    sdl.send_redraw_event(*mandelbrot_renderer);
}
