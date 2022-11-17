#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"

class Tile {
    private:
        int x, y; // coordinate for drawing onto screen 
        int size; // size (in pixels) of the tile
        int val; // value of the tile in Game of Life determines the livingness of tile
        SDL_Color color; // the color of the tile
        SDL_Rect rect; // the 
    public: 
        // default constructor
        Tile();
        

        // ======== Getters ========

        // returns the x coord of tile
        int getx() { return x; };
        // returns the y coord of tile
        int gety() { return y; };
        // returns the value property
        int getval() { return val; };


        // ======== Setters ========

        // sets the x coord to given value
        void setx( int n_x ) { x = n_x; };
        // sets the y coord to given value
        void sety( int n_y ) { y = n_y; };
        // set the value property
        void setval( int n_val ) { val = n_val; };
        // sets the color value of the tile 
        void setcolor( SDL_Color n_color ) { color = n_color; };

        // draw to the screen using a given renderer
        void draw( SDL_Renderer *window_renderer);
};

#endif // TILE_H