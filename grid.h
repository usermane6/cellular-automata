#include "tile.h"
#include "constants.h"

#include "SDL2/SDL.h"

class Grid {
    private:
        Tile all_tiles[constants::T_TILES];
        int id_from_pos( int x, int y );
    public:
        Grid();
        void make_tiles();
        void draw_all( SDL_Renderer* );
};
