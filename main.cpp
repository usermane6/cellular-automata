#include <iostream>
#include "SDL2/SDL.h"

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

    Grid m_grid( 2 ); 
    // m_grid.make_tiles();
    m_grid.draw_all(m_window_renderer);
    // m_grid.draw_one(m_window_renderer, 0, 0);

    SDL_Event event;
    bool is_holding_space = false, is_holding_color = false;

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if (!is_holding_space) {
                        m_grid.draw_all(m_window_renderer);
                        // is_holding_space = true;
                    }
                }
                // todo remove
                if (event.key.keysym.sym == SDLK_c) {
                    if (!is_holding_color) {
                        // m_grid.change_color_mode();
                        m_grid.draw_all(m_window_renderer);
                        is_holding_color = true;
                    }
                }

            }

            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    is_holding_space = false;
                }
                if (event.key.keysym.sym == SDLK_c) {
                    is_holding_color = false;
                }
            }
        }
    m_grid.iterate_langton(m_window_renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit;

    return EXIT_SUCCESS;
}