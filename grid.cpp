#include "grid.h"
#include "tile.h"

#include "SDL2/SDL.h"

Grid::Grid( int n_h, int n_w, int n_tile_size ) {
    h = n_h;
    w = n_w;
    tile_size = n_tile_size;

    cols = w / tile_size;
    rows = h / tile_size;

    tile_grid[w][h];

}

void Grid::make_tiles() {
    // declare color variable
    // used for the color of each tile
    SDL_Color color;

    for (int i = 0; i < w / tile_size; i ++) {
        for (int j = 0; j < h / tile_size; j++) {
            // selec tile color definitions
            color.r = (255 * j) / h;
            color.g = 100;
            color.b = (255 * i) / w;

            // create new tile
            Tile new_tile( i * tile_size, j * tile_size, tile_size, color);
            tile_grid[i][j] = new_tile; 
        }
    }   
}

void Grid::draw_all( SDL_Renderer * window_renderer ) {

    

}