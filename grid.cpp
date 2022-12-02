#include "grid.h"
#include "constants.h"

#include "SDL2/SDL.h"
#include <iostream>
#include <math.h>
#include <algorithm>

// TODO make dedicated iterae function that operates based on mode


Grid::Grid( int n_mode ) {

    mode = n_mode;

    for (int i = 0; i < constants::T_TILES; i ++) {
            switch ( mode ) {
            case 0 :
                all_tiles[i] = rand() % 2;
                break;
            case 1 :
                all_tiles[i] = rand() % 3;
                break;
            case 2 :
                all_tiles[i] = 1;
                break;
        }
    }
}

void Grid::draw_all( SDL_Renderer * window_renderer ) {

    SDL_Color color;
    SDL_Rect rect;
    rect.h = constants::SQ_SIZE;
    rect.w = constants::SQ_SIZE;

    int x = 0, y = 0;

    for (int t : all_tiles) {

        // std::cout << t << " ";

        rect.x = x * constants::SQ_SIZE;
        rect.y = y * constants::SQ_SIZE;

        switch (mode) {
            case 0: case 2:
                color.r = 255 * t;
                color.g = 255 * t;
                color.b = 255 * t;
                break;
            case 1:
                color.r = 0;
                color.g = 0;
                color.b = 0;

                if (t == 0) color.r = 255;
                else if (t == 1) color.g = 255;
                else if (t == 2) color.b = 255;
                break;   
        }

        SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawRect(window_renderer, &rect);
        SDL_RenderFillRect(window_renderer, &rect);
        SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);

        x++; 

        if ( x >= constants::G_WIDTH ) {
            x = 0;
            y++;
        } 

    }

    SDL_RenderPresent(window_renderer);

}

void Grid::draw_one( int x, int y, SDL_Renderer * window_renderer ) {
    SDL_Color color;
    SDL_Rect rect;
    rect.h = constants::SQ_SIZE;
    rect.w = constants::SQ_SIZE;

    rect.x = x * constants::SQ_SIZE;
    rect.y = y * constants::SQ_SIZE;

    int id = id_from_pos( x, y );
    int t = all_tiles[id];

    switch (mode) {
        case 0: case 2:
            color.r = 255 * t;
            color.g = 255 * t;
            color.b = 255 * t;
            break;
        case 1:
            color.r = 0;
            color.g = 0;
            color.b = 0;

            if (t == 0) color.r = 255;
            else if (t == 1) color.g = 255;
            else if (t == 2) color.b = 255;
            break;   
    }

    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawRect(window_renderer, &rect);
    SDL_RenderFillRect(window_renderer, &rect);
    SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(window_renderer);
}

int Grid::id_from_pos( int x, int y ) {
    if (!is_in_bounds( x, y )) { return -1; }
    return ((constants::G_WIDTH - 1) * y) + x + y;
}

int Grid::id_from_pos( int pos[2] ) {
    if (!is_in_bounds( pos[0], pos[1] )) { return -1; }
    return ((constants::G_WIDTH - 1) * pos[1]) + pos[0] + pos[1];
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

            if ( !is_in_bounds(x + i, y + j) || (i == 0 && j == 0) ) continue;

            id = id_from_pos( x + i, y + j );
            
            if (copy_of_tiles[id] == 1) num_alive ++;
        }
    }
    // std:: cout << num_alive << std::endl;

    return num_alive;
}

int Grid::neighbors_with_value( int x, int y, int value ) {
    int id, num = 0;

    for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {
            id = id_from_pos( x + i, y + j );

            if ( !is_in_bounds(x + i, y + j) || (i == 0 && j == 0) ) continue;
            
            if ( copy_of_tiles[id] == value ) num ++;
        }
    }
    return num;
}

int Grid::dist_from_center( int x, int y ) {
    return std::sqrt( pow( ( x - ( constants::G_WIDTH / 2 ) ), 2 ) + pow( ( y - ( constants::G_HEIGHT / 2 ) ), 2 ) );
}

void Grid::iterate_conway() {
    int id, num_alive;
    std::copy(std::begin(all_tiles), std::end(all_tiles), std::begin(copy_of_tiles));

    int x = 0, y = 0;

    for (int i = 0; i < constants::T_TILES; i++) {

        num_alive = alive_neighbors(x, y);


        if (copy_of_tiles[1] == 0 && num_alive == 3) all_tiles[i] = 1;

        else if (num_alive < 2 || num_alive > 3) all_tiles[i] = 0;

        
        x++; 

        if ( x >= constants::G_WIDTH ) {
            x = 0;
            y++;
        } 
    }
}

void Grid::iterate_rps() {
    int x = 0, y = 0;
    int r, p, s;
    int thresh = constants::RPS_THRESHHOLD;

    std::copy(std::begin(all_tiles), std::end(all_tiles), std::begin(copy_of_tiles));
   
    for (int i = 0; i < constants::T_TILES; i++) {

        r = neighbors_with_value(x, y, 0);
        p = neighbors_with_value(x, y, 1);
        s = neighbors_with_value(x, y, 2);

        if (copy_of_tiles[i] == 0 && p > thresh) all_tiles[i] = 1;
        else if (copy_of_tiles[i] == 1 && s > thresh) all_tiles[i] = 2;
        else if (copy_of_tiles[i] == 2 && r > thresh) all_tiles[i] = 0;

        x++; 
    
        if ( x >= constants::G_WIDTH ) {
            x = 0;
            y++;
        } 

    } 
}

void Grid::iterate_rand_rps() {
    int x = 0, y = 0;
    int r, p, s, rand_val;
    int thresh = constants::RPS_THRESHHOLD;
    
    std::copy(std::begin(all_tiles), std::end(all_tiles), std::begin(copy_of_tiles));
   
    for (int i = 0; i < constants::T_TILES; i++) {

        r = neighbors_with_value(x, y, 0);
        p = neighbors_with_value(x, y, 1);
        s = neighbors_with_value(x, y, 2);

        rand_val = rand() % 3;

        if (copy_of_tiles[i] == 0 && p > thresh + rand_val) all_tiles[i] = 1;
        else if (copy_of_tiles[i] == 1 && s > thresh + rand_val) all_tiles[i] = 2;
        else if (copy_of_tiles[i] == 2 && r > thresh + rand_val) all_tiles[i] = 0;

        x++; 
    
        if ( x >= constants::G_WIDTH ) {
            x = 0;
            y++;
        } 

    } 
}

void Grid::iterate_langton( SDL_Renderer * window_renderer ) {
    
    int ant_id = id_from_pos( ant_pos );
    // std::cout << "iterating !!";

    if ( is_ant_dead ) return;

    // std::cout << "not dead!";
    // TODO cleanup this switch, maybe add move ant function
    switch ( all_tiles[ant_id] ) {
        case 0:
            // turn left on black tile
            all_tiles[ant_id] = 1;
            turn_ant( -1 );
            draw_one( ant_pos[0], ant_pos[1], window_renderer);
            move_ant();

            break;
        case 1:
             // turn right on white tile
            all_tiles[ant_id] = 0;
            turn_ant( 1 );
            draw_one( ant_pos[0], ant_pos[1], window_renderer);
            move_ant();
            
            break;
            
    }
}

void Grid::turn_ant( int direction ) {
    ant_facing += direction;
    if (ant_facing == 4) { ant_facing = 0; } 
    else if (ant_facing == -1) { ant_facing = 3; }
}

void Grid::move_ant() {

    ant_pos[0] += constants::DIRECTIONS[ant_facing][0];
    ant_pos[1] += constants::DIRECTIONS[ant_facing][1];

    if ( !is_in_bounds(ant_pos[0], ant_pos[1]) ) is_ant_dead = true; 

}