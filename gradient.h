#ifndef GRADIENT_H
#define GRADIENT_H

#include <SDL2/SDL.h>

class Gradient {
    private:
        SDL_Color start_color;
        SDL_Color end_color;

    public:
        Gradient(SDL_Color n_start_color, SDL_Color n_end_color);
        Gradient(){};
        void set_colors(SDL_Color n_start_color, SDL_Color n_end_color);
        SDL_Color get_mid_color( double percent );
};

#endif