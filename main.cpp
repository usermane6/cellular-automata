#include <iostream>
#include "SDL2/SDL.h"
// #include "SDL2/SDL_ttf.h"

#include "grid.hpp"
#include "constants.hpp"

// void display_fps(double fps, SDL_Renderer* window_renderer) {
//     TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
//     SDL_Color t_color = { 0, 255, 0, 0 };


// }


int main( int argc, char *argv[] ) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = SDL_CreateWindow( "Cells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::W_WIDTH, constants::W_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if ( window = NULL ) {
        std::cout << "Error Creating Window" << SDL_GetError() << "\n";
        return 1;
    }

    Grid m_grid( Grid::war ); 
    m_grid.draw_all(m_window_renderer);

    Uint32 start_time, frame_time;
    double fps;

    SDL_Event event;

    // main loop 
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
        start_time = SDL_GetTicks();

        m_grid.iterate(m_window_renderer);

        frame_time = SDL_GetTicks() - start_time;
        fps = (frame_time > 0) ? 1000.0 / frame_time : 0.0;
    }

    SDL_DestroyWindow(window);
    SDL_Quit;

    return EXIT_SUCCESS;
}