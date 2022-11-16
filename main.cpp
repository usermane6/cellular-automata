#include <iostream>
#include "SDL2/SDL.h"

#include "tile.h"
#include "grid.h"

const int WIDTH = 800, HEIGHT = 800; // dimensions of window
const int SQ_SIZE = 10; // size of tiles

int main( int argc, char *argv[] ) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "Cells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if ( window = NULL ) {
        std::cout << "Error Creating Window" << SDL_GetError() << "\n";
        return 1;
    }

    Grid m_grid;
    m_grid.make_tiles();
    m_grid.draw_all(m_window_renderer);
    // m_grid.draw_one(m_window_renderer, 0, 0);

    SDL_Event windowEvent;
    while (true) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit;

    return EXIT_SUCCESS;
}