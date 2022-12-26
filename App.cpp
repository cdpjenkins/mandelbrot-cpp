#include "App.hpp"

void App::main_loop() {
    int rc;

    Uint32 start_time;

    render_mandie();

    bool quit = false;
    // This is the main event loop. it's kind of annoying to have to have SDL stuff in here. Maybe
    // turn this into an elaborate system of callbacks at some point.
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
                            mandie->increase_depth();
                            render_mandie();
                            break;
                        case SDL_SCANCODE_L:
                            cout << "decrease depth" << endl;
                            mandie->decrease_depth();
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
                        mandie->zoom_in_to(e.button.x, e.button.y);
                    } else {
                        mandie->zoom_out_to(e.button.x, e.button.y);
                    }

                    render_mandie();

                    break;
            }
        }

        if (config.auto_zoom) {
            mandie->zoom_in_to(config.zoom_to);
            render_mandie();

            if (mandie->zoom_size < config.max_zoom) {
                break;
            }
        }
    }
}

void App::render_mandie() {
    // TODO - really want to do this on a separate thread so the GUI doesn't freeze
    // whilst it's happening
    mandie->render_to_buffer();
    png_saver.save_png(*mandie);
    sdl.copy_rendered_mandie_to_screen(*mandie);
}
