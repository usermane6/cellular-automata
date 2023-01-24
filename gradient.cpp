#include "gradient.h"
#include <SDL2/SDL.h>

Gradient::Gradient(SDL_Color n_start_color, SDL_Color n_end_color) {
    start_color = n_start_color;
    end_color = n_end_color;
}

void Gradient::set_colors(SDL_Color n_start_color, SDL_Color n_end_color) {
    start_color = n_start_color;
    end_color = n_end_color;
}

SDL_Color Gradient::get_mid_color(double percent) {
    SDL_Color return_color;
    return_color.r = ((start_color.r * percent) + (end_color.r * (1 - percent))) / 2; 
    return_color.g = ((start_color.g * percent) + (end_color.g * (1 - percent))) / 2; 
    return_color.b = ((start_color.b * percent) + (end_color.b * (1 - percent))) / 2; 
    return return_color;
}