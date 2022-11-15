#include <iostream>
#include "SDL2/SDL.h"
#include "tile.h"

const int WIDTH = 800, HEIGHT = 600;
const int SQ_SIZE = 10; // size of tiles

int main( int argc, char *argv[] ) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window *window = SDL_CreateWindow( "Cells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window = NULL) {
        std::cout << "Error Creating Window" << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Color m_color;

    for (int x = 0; x < WIDTH; x += SQ_SIZE) {
        for (int y = 0; y < HEIGHT; y += SQ_SIZE) {
            m_color.r = (255 * (HEIGHT - y)) / HEIGHT;
            m_color.g = 100;
            m_color.b = (255 * x) / WIDTH;


            Tile m_tile(x, y, SQ_SIZE, m_color); 
            m_tile.draw(m_window_renderer);
        }
    }

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