#ifndef SDLSURFACERAII_HPP
#define SDLSURFACERAII_HPP

#include <SDL.h>

class SDLSurfaceRAII {
public:
    SDLSurfaceRAII(SDL_Surface* surface) : surface(surface) {
        if (!surface) {
            throw runtime_error("Failed creating new surface: "s + SDL_GetError());
        }
    }

    ~SDLSurfaceRAII() {
        if (surface != nullptr) {  
            SDL_FreeSurface(surface);
        }
    }

    SDL_Surface* get() { return surface; }

private:
    SDL_Surface* surface;
};

#endif // SDLSURFACERAII_HPP