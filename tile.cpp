#include "tile.h"
#include "SDL2/SDL.h"
#include <iostream>

Tile::Tile( int n_x, int n_y, int n_size, SDL_Color n_color ) {
    x = n_x;
    y = n_y;
    size = n_size;
    color = n_color;
    // std::cout << rect.y << "\n";
}

void Tile::draw(SDL_Renderer * window_renderer) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = size;
    rect.w = size;

    // std::cout << rect.x << " " << rect.y << "\n";
    // SDL_RenderClear(window_renderer);
    SDL_SetRenderDrawColor(window_renderer, 
                            color.r, 
                            color.g, 
                            color.b, 
                            255);

    SDL_RenderDrawRect(window_renderer, &rect);
    SDL_RenderFillRect(window_renderer, &rect);
    SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(window_renderer);
}