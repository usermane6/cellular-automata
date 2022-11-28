#ifndef GRID_H
#define GRID_H

#include "constants.h"

#include "SDL2/SDL.h"

class Grid {
    private:
        int mode;
        int all_tiles[ constants::T_TILES ] = {}; // contains all tiles in the grid
        int copy_of_tiles[ constants::T_TILES ]; // clone of all tiles, used for making new generations/iterating

        // takes an (x, y) position an turns it into an id for the all_tiles array
        int id_from_pos( int x, int y ); 
        // checks if a given position is in the bounds of the array
        bool is_in_bounds( int x, int y);
        // returns the number of neighbors with value 1
        int alive_neighbors( int x, int y);

        int neighbors_with_value(int x, int y, int value);

        int dist_from_center( int x, int y);

    public:
        Grid( int n_mode );
        // calls the draw function for every tile in the all_tiles array
        void draw_all( SDL_Renderer *window_renderer );
        // iterates to a new generation using the ruleset of Conway's Game of Life
        void iterate_conway();
        // iterates using rock paper scissors rules
        void iterate_rps();
        // iterats using rps, but randomly increases threshold
        void iterate_rand_rps();
};

#endif 