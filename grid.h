#ifndef GRID_H
#define GRID_H

#include "constants.h"
#include "gradient.h"

#include "SDL2/SDL.h"

//todo cleanup | organizaion
//todo id to pos function

class Grid {
    private:
        int mode; // what mode to render the colors
        int all_tiles[ constants::T_TILES ] = {}; // contains all tiles in the grid
        int copy_of_tiles[ constants::T_TILES ]; // clone of all tiles, used for making new generations/iterating
        bool do_update[ constants::T_TILES ];
        Gradient t_grad;

        // ------ Langton's ant variables -------

        int ant_pos[2] = { constants::G_CENTER[0] * 1, constants::G_CENTER[1] * 1 }; // position of ant on grid
        int ant_facing = 0; // 0 - 3 integer based on which way the ant is facing, 0 is North
        bool is_ant_dead = false;

        // takes an x, y position an turns it into an id for the all_tiles array
        int id_from_pos( int x, int y ); 
        /*
        takes an position array and turns it into an id for the all_tiles array
        \param pos  a list of two ints that are an x, y on the grid 
        */
        int id_from_pos( int pos[2] );
        // checks if a given position is in the bounds of the array

        int* pos_from_id( int id, int* pos );

        bool is_in_bounds( int x, int y);
        // returns the number of neighbors with value 1
        int alive_neighbors( int x, int y);
        // returns all neighbors of a given point with certain value
        int neighbors_with_value( int x, int y, int value, bool or_greater = false );
        // calculates the distance from the center point

        int dist_from_center( int x, int y);
        // draws a single tile to screen, without clearing the renderer
        void draw_one( int x, int y, SDL_Renderer * window_renderer );
        // 
        SDL_Color get_tile_color( int id, int t );
        // iterates to a new generation using the ruleset of Conway's Game of Life
        void iterate_conway( int x, int y );
        // iterates using rock paper scissors rules
        void iterate_rps( int x, int y );

        void iterate_true_rps( int x, int y );
        // iterates using rps, but randomly increases threshold
        void iterate_rand_rps( int x, int y );

        // iterates using langtons ant
        void iterate_langton( SDL_Renderer * window_renderer );
        // changes the directon of the ant right ( 1 ) or left ( -1 )
        void turn_ant( int direction );
        // moves the ant in its current diection
        void move_ant();

        /* 
        first custom algorithm, assigns each a random card value
        for each tile, checks if it wins a certain amount of games against the neighbors 
        then adjusts the value of tile 
        */
        void iterate_war( int x, int y );

    public:

        // enums enums enums!!!
        // different drawing methods
        enum draw_modes {
            gradient = 0,
            conway,
            rps,
            langton,
            war,
        };
        // diffeent names for problems, simply for readability
        enum tile_types {
            black = 0,
            white,
            rock = 0,
            paper,
            scissors,
        };

        Grid( int n_mode );
        // calls the draw function for every tile in the all_tiles array
        void draw_all( SDL_Renderer* window_renderer );
        // creates a new iteration 
        void iterate( SDL_Renderer* window_renderer );

        void reset( SDL_Renderer* window_renderer );
        void reset( SDL_Renderer* window_renderer, int n_mode );

};

#endif 