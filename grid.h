#include "tile.h"
#include "SDL2/SDL.h"

class Grid {
    private:
        int h, w, tile_size, cols, rows; 
        Tile** tile_grid;
        void make_tiles();
    public:
        Grid( int, int, int );
        void draw_all( SDL_Renderer* );
};
