#ifndef GRID_H
#define GRID_H

#include "tile.h"
#include "constants.h"

#include "SDL2/SDL.h"

class Grid {
    private:
        int all_tiles[ constants::T_TILES ] = {}; // contains all tiles in the grid
        int copy_of_tiles[constants::T_TILES]; // clone of all tiles, used for making new generations/iterating

        enum color_modes {
            white,
            gradient,
            center,
            last,
        };

        int current_mode = white;

        // takes an (x, y) position an turns it into an id for the all_tiles array
        int id_from_pos( int x, int y ); 
        // checks if a given position is in the bounds of the array
        bool is_in_bounds( int x, int y);
        // returns the number of neighbors with value 1
        int alive_neighbors( int x, int y);

        int dist_from_center( int x, int y);

    public:
        Grid();

        // sets all the tiles to correct positions and changes their color
        void make_tiles();
        // calls the draw function for every tile in the all_tiles array
        void draw_all( SDL_Renderer *window_renderer );
        // iterats to a new generation using the ruleset of Conway's Game of Life
        void iterate_conway();

        void change_color_mode();
};

#endif 