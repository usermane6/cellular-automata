#include <iostream>
#include "SDL2/SDL.h"

#include "tile.h"
#include "grid.h"
#include "constants.h"

int main( int argc, char *argv[] ) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "Cells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::W_WIDTH, constants::W_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if ( window = NULL ) {
        std::cout << "Error Creating Window" << SDL_GetError() << "\n";
        return 1;
    }

    Grid m_grid;
    m_grid.make_tiles();
    m_grid.draw_all(m_window_renderer);
    // m_grid.draw_one(m_window_renderer, 0, 0);

    SDL_Event event;
    bool is_holding = false;

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if (!is_holding) {
                        m_grid.iterate_conway();
                        m_grid.draw_all(m_window_renderer);
                        is_holding = true;
                    }
                }
            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    is_holding = false;
                }
            }
        }

    }

    SDL_DestroyWindow(window);
    SDL_Quit;

    return EXIT_SUCCESS;
}