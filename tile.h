#ifndef TILE_H
#define TILE_H

#include "SDL2/SDL.h"

class Tile {
    private:
        int x, y, size; 
        SDL_Color color;
    public: 
        // constructors
        Tile();

        // getters
        int getx() { return x; };
        int gety() { return y; };

        //setters
        void setx( int n_x ) { x = n_x; };
        void sety( int n_y ) { y = n_y; };
        void setcolor( SDL_Color n_color ) { color = n_color; };

        void draw( SDL_Renderer* );
};

#endif // TILE_H