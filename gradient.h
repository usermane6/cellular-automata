#ifndef GRADIENT_H
#define GRADIENT_H

#include <SDL2/SDL.h>

class Gradient {
    private:
        SDL_Color start_color;
        SDL_Color end_color;

    public:
        SDL_Color get_mid_color( double percent );
};

#endif