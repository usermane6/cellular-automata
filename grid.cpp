#include "grid.h"
#include "tile.h"

#include "SDL2/SDL.h"

Grid::Grid(int n_h, int n_w) {
    h = n_h;
    w = n_w;
    tile_grid[w][h];
}