#include "SDL2/SDL.h"

class Tile {
    private:
        int x, y, size; 
        SDL_Color color;
    public: 
        Tile( int, int, int, SDL_Color );
        int getx() { return x; };
        int gety() { return y; };
        void draw( SDL_Renderer* );
};