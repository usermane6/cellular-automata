#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"

#include "grid.hpp"
#include "constants.hpp"

void display_fps(double fps, SDL_Renderer* window_renderer, TTF_Font* font, SDL_Surface* surface, SDL_Texture* texture) {
    // todo cleanup
    SDL_Color t_color = { 0, 0, 0, 0 };
    SDL_Color box_color = { 255, 255, 255, 0};
    char* fps_str = const_cast<char*>(std::to_string(fps).c_str()); // converts fps param to char*, that SDL_ttf uses
    
    surface = TTF_RenderText_Solid(font, fps_str, t_color);
    texture = SDL_CreateTextureFromSurface(window_renderer, surface);

    int h, w; // height/width of text
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_Rect rect = {0, 0, w, h};
    SDL_SetRenderDrawColor(window_renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(window_renderer, &rect);
    SDL_RenderFillRect(window_renderer, &rect);
    SDL_RenderCopy(window_renderer, texture, NULL, &rect);
    SDL_RenderPresent(window_renderer);
}

int main( int argc, char *argv[] ) {
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = SDL_CreateWindow("Cells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, constants::W_WIDTH, constants::W_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if ( window = NULL ) {
        std::cout << "Error Creating Window" << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    if (TTF_Init() == -1) {
        std::cout << "Error Loading Font" << TTF_GetError() << "\n";
        return EXIT_FAILURE;
    }

    TTF_Font* arial = TTF_OpenFont("DMMono-Medium.ttf", constants::FONT_SIZE);
    SDL_Surface* text_surface;
    SDL_Texture* text_texture;

    Grid m_grid( Grid::langton ); 
    m_grid.draw_all(m_window_renderer);

    Uint32 start_time, frame_time;
    double fps, fps_avg = 0;

    SDL_Event event;

    // main loop 
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }

            if (event.type == SDL_KEYDOWN) {
                // if (event.key.keysym.sym == SDLK_r) {
                //     m_grid.reset();
                // }
                switch (event.key.keysym.sym) {
                    case SDLK_r:
                        m_grid.reset( m_window_renderer );
                        break;
                    case SDLK_1:
                        m_grid.reset( m_window_renderer, Grid::conway );
                        break;
                    case SDLK_2:
                        m_grid.reset( m_window_renderer, Grid::rps );
                        break;
                }
            }
        }
        start_time = SDL_GetTicks();

        m_grid.iterate(m_window_renderer);

        frame_time = SDL_GetTicks() - start_time;
        
        fps = (frame_time > 0) ? 1000.0 / frame_time : 0.0;
        fps_avg = fps_avg == 0 ? fps : (fps_avg + fps) / 2;
        display_fps(fps, m_window_renderer, arial, text_surface, text_texture);
    }

    std::cout << "Average Fps: " << fps_avg;


    // end of game
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);   

    TTF_CloseFont(arial);

    TTF_Quit();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}