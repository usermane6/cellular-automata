#include "tile.h"
#include "grid.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include <iostream>

Grid::Grid() {
    // std::cout << "making grid \n";

    Tile all_tiles[constants::T_TILES] = {};
}

void Grid::make_tiles() {
    SDL_Color color;
    for (int row = 0; row < constants::G_HEIGHT; row++) {
        for (int col = 0; col < constants::G_WIDTH; col++) {
            // gets the index of the 1d array based on an x (col) and a y (row)
            int id = id_from_pos(row, col);

            color.r = (row * 255) / constants::G_HEIGHT; 
            color.b = (col * 255) / constants::G_WIDTH;

            all_tiles[id].setx(col * constants::SQ_SIZE);
            all_tiles[id].sety(row * constants::SQ_SIZE);
            all_tiles[id].setcolor(color);

        }
    }
}

void Grid::draw_all( SDL_Renderer * window_renderer ) {

    for (Tile t : all_tiles) {
        t.draw(window_renderer);
    }

}

int Grid::id_from_pos( int x, int y ) {
    return ((constants::G_WIDTH - 1) * x) + x + y;
}