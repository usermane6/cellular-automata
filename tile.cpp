#include "tile.h"
#include "SDL2/SDL.h"
#include "constants.h"
#include <iostream>

Tile::Tile() {
    // std::cout << "making tile! \n";

    x = 0;
    y = 0;
    size = constants::SQ_SIZE;
    color = { 255, 255, 255 };

    // std::cout << "tile made! \n";
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