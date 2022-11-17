#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include "constants.h"

#include "SDL2/SDL.h"

class Grid {
    private:
        Tile all_tiles[ constants::T_TILES ]; // contains all tiles in the grid
            
        Tile copy_of_tiles[constants::T_TILES]; // clone of all tiles, used for making new generations/iterating

        // takes an (x, y) position an turns it into an id for the all_tiles array
        int id_from_pos( int x, int y ); 

        // checks if a given position is in the bounds of the array
        bool is_in_bounds( int x, int y);

        
        int alive_neighbors( int x, int y);

    public:
        Grid();

        // sets all the tiles to correct positions and changes their color
        void make_tiles();

        // calls the draw function for every tile in the all_tiles array
        void draw_all( SDL_Renderer *window_renderer );

        void iterate_conway();
};

#endif 