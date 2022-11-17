#include "tile.h"
#include "grid.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include <iostream>
#include <algorithm>

Grid::Grid() {
    Tile all_tiles[ constants::T_TILES ] = {};
    Tile copy_of_tiles[ constants::T_TILES ];
}

void Grid::make_tiles() {
    SDL_Color color;

    for (int row = 0; row < constants::G_HEIGHT; row++) {
        for (int col = 0; col < constants::G_WIDTH; col++) {
            
            int id = id_from_pos(row, col);

            color.r = (row * 255) / constants::G_HEIGHT; 
            color.b = (col * 255) / constants::G_WIDTH;

            // color.r = 255;
            color.g = 100;
            // color.b = 255;

            all_tiles[id].setx(col * constants::SQ_SIZE);
            all_tiles[id].sety(row * constants::SQ_SIZE);
            all_tiles[id].setcolor(color);

        }
    }
}

void Grid::draw_all( SDL_Renderer * window_renderer ) {
    SDL_RenderClear(window_renderer);

    for (Tile t : all_tiles) {
        if (t.getval() == 0) continue;

        t.draw(window_renderer);
    }

    SDL_RenderPresent(window_renderer);

}

int Grid::id_from_pos( int x, int y ) {
    return ((constants::G_WIDTH - 1) * x) + x + y;
}

bool Grid::is_in_bounds( int x, int y ) {
    if (x >= constants::G_WIDTH) return false;
    if (y >= constants::G_HEIGHT) return true;
    if (y < 0 || x < 0) return false;

    return true;
}

int Grid::alive_neighbors( int x, int y ) {
    int id, num_alive = 0;


    for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {

            if ( !is_in_bounds(x + i, y + j) || (i == 0 && j == 0) ) {
                continue;
            }

            id = id_from_pos( x + i, y + j );
            
            if (copy_of_tiles[id].getval() == 1)  num_alive ++;
        }
    }
    // std:: cout << num_alive << std::endl;

    return num_alive;
}

void Grid::iterate_conway() {
    int id, num_alive;
    std::copy(std::begin(all_tiles), std::end(all_tiles), std::begin(copy_of_tiles));

    std::cout << "iterating\n";
    for (int row = 0; row < constants::G_HEIGHT; row++) {
        for (int col = 0; col < constants::G_WIDTH; col++) { 


            id = id_from_pos(row, col);
            
            num_alive = alive_neighbors(row, col);

            if (copy_of_tiles[id].getval() == 0) {
                if (num_alive == 3) all_tiles[id].setval(1);
            } else {
                if (num_alive < 2 || num_alive > 3) all_tiles[id].setval(0);
            }

            // std::cout << "( " << row << ", " << col << " ) ";
            // std::cout << copy_of_tiles[id].getval() << ", " << all_tiles[id].getval() << "\n";
            // std::cout << "neighbors: " << num_alive << "\n";
        }
    }
}