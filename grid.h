#ifndef GRID_H
#define GRID_H

#include "constants.h"

#include "SDL2/SDL.h"

class Grid {
    private:

        

        int mode; // what mode to render the colors
        int all_tiles[ constants::T_TILES ] = {}; // contains all tiles in the grid
        int copy_of_tiles[ constants::T_TILES ]; // clone of all tiles, used for making new generations/iterating

        // TODO use enum for tile types
        // ------ Langton's ant variables -------

        int ant_pos[2] = { constants::G_CENTER[0] * 1, constants::G_CENTER[1] * 1 }; // position of ant on grid
        int ant_facing = 0; // 0 - 3 integer based on which way the ant is facing, 0 is North
        bool is_ant_dead = false;

        // takes an x, y position an turns it into an id for the all_tiles array
        int id_from_pos( int x, int y ); 
        // takes an position array of length 2 and turns it into an id for the all_tiles array
        int id_from_pos( int pos[2] );
        // checks if a given position is in the bounds of the array
        bool is_in_bounds( int x, int y);
        // returns the number of neighbors with value 1
        int alive_neighbors( int x, int y);
        // returns all neighbors of a given point with certain value
        int neighbors_with_value( int x, int y, int value );
        // calculates the distance from the center point
        int dist_from_center( int x, int y);
        // changes the directon of the ant right ( 1 ) or left ( -1 )
        void turn_ant( int direction );

        void move_ant();

        void draw_one( int x, int y, SDL_Renderer * window_renderer );


    public:

        // enums enums enums!!!

        enum draw_modes {
            conway = 0,
            rps,
            langton,
        };

        Grid( int n_mode );
        // calls the draw function for every tile in the all_tiles array
        void draw_all( SDL_Renderer *window_renderer );
        // iterates to a new generation using the ruleset of Conway's Game of Life
        void iterate_conway();
        // iterates using rock paper scissors rules
        void iterate_rps();
        // iterates using rps, but randomly increases threshold
        void iterate_rand_rps();
        // iterates using langtons ant
        void iterate_langton( SDL_Renderer * window_renderer );

};

#endif 