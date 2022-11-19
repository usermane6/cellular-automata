#include "tile.h"
#include "grid.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include <iostream>
#include <math.h>
#include <algorithm>

Grid::Grid() {
}

// void Grid::make_tiles() {
//     SDL_Color color;

//     for (int row = 0; row < constants::G_HEIGHT; row++) {
//         for (int col = 0; col < constants::G_WIDTH; col++) {
            
//             int id = id_from_pos(row, col);

//             // color.r = (row * 255) / constants::G_HEIGHT; 
//             // color.b = (col * 255) / constants::G_WIDTH;

//             color.r = 255;
//             color.g = 255;
//             color.b = 255;

//             all_tiles[id].setx(col * constants::SQ_SIZE);
//             all_tiles[id].sety(row * constants::SQ_SIZE);
//             all_tiles[id].setcolor(color);

//         }
//     }
// }

// void Grid::draw_all( SDL_Renderer * window_renderer ) {
//     SDL_RenderClear(window_renderer);

//     for (int : all_tiles) {
//         if (t) continue;

//         t.draw(window_renderer);
//     }

//     SDL_RenderPresent(window_renderer);

// }

void Grid::draw_all( SDL_Renderer * window_renderer) {

    SDL_Color color;
    SDL_Rect rect;

    int x = 0, y = 0;

    for (int t : all_tiles) {
        


    }

}

int Grid::id_from_pos( int x, int y ) {
    return ((constants::G_WIDTH - 1) * x) + x + y;
}

bool Grid::is_in_bounds( int x, int y ) {
    if (x >= constants::G_WIDTH) return false;
    if (y >= constants::G_HEIGHT) return false;
    if (y < 0 || x < 0) return false;

    return true;
}

int Grid::alive_neighbors( int x, int y ) {
    int id, num_alive = 0;


    for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {

            if ( !is_in_bounds(x + i, y + j) || (i == 0 && j == 0) ) {
                continue;
            }

            id = id_from_pos( x + i, y + j );
            
            if (copy_of_tiles[id] == 1) num_alive ++;
        }
    }
    // std:: cout << num_alive << std::endl;

    return num_alive;
}

int Grid::dist_from_center( int x, int y ) {
    return std::sqrt( pow( ( x - ( constants::G_WIDTH / 2 ) ), 2 ) + pow( ( y - ( constants::G_HEIGHT / 2 ) ), 2 ) );
}

void Grid::iterate_conway() {
    int id, num_alive;
    std::copy(std::begin(all_tiles), std::end(all_tiles), std::begin(copy_of_tiles));

    std::cout << "iterating\n";
    for (int row = 0; row < constants::G_HEIGHT; row++) {
        for (int col = 0; col < constants::G_WIDTH; col++) { 


            id = id_from_pos(row, col);
            
            num_alive = alive_neighbors(row, col);

            if (copy_of_tiles[id] == 0) {
                if (num_alive == 3) {
                    all_tiles[id] = 1;
                }
            } else {
                if (num_alive < 2 || num_alive > 3) {
                    all_tiles[id] = 0;
                } 
            }
            
            // std::cout << all_tiles[id].getval() << std::endl;

            // std::cout << "( " << row << ", " << col << " ) ";
            // std::cout << copy_of_tiles[id].getval() << ", " << all_tiles[id].getval() << "\n";
            // std::cout << "neighbors: " << num_alive << "\n";
        }
    }
}

// void Grid::change_color_mode() {
//     current_mode ++;
//     if (current_mode == last) current_mode = 0;

//     SDL_Color color;
//     int id;
    
//     for (int row = 0; row < constants::G_HEIGHT; row++) {
//         for (int col = 0; col < constants::G_WIDTH; col++) {

//             switch (current_mode) {
//                 case white:
//                     color.r = 255;
//                     color.g = 255;
//                     color.b = 255;
//                     break;

//                 case gradient:
//                     color.r = (row * 255) / constants::G_HEIGHT;
//                     color.g = 100;
//                     color.b = (col * 255) / constants::G_WIDTH;
//                     break;

//                 case center:
//                     int value = ( ( 60 - dist_from_center(row, col) ) * 255 ) / 60;
//                     color.r = value;
//                     color.g = value;
//                     color.b = value;
//                     break;        
//             }
            
//             id = id_from_pos(row, col);

//             all_tiles[id].setcolor(color);

//         }
//     }
// }