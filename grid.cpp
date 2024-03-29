#include "grid.h"
#include "constants.h"
#include "gradient.h"

#include "SDL2/SDL.h"

#include <iostream>
#include <math.h>
// #include <algorithm>

// TODO make single tile a certain value
// TODO fixed shapes?

SDL_Color random_color() {
    SDL_Color new_color = {};
    new_color.r = rand() % 255;
    new_color.g = rand() % 255;
    new_color.b = rand() % 255;
    return new_color;
}

SDL_Color all_colors[101] = {};

Grid::Grid( int n_mode ) {

    for(int c = 0; c < 101; c++){ 
        all_colors[c] = random_color();
    };

    mode = n_mode;
    int* pos = new int[2];
    int y;
    t_grad.set_colors(colors::t_color1, colors::t_color2);

    for (int i = 0; i < constants::T_TILES; i ++) {
        do_update[i] = true;
        switch ( mode ) {
            case gradient:
                y = pos_from_id(i, pos)[1];
                all_tiles[i] = std::round(100 * ( (y * 1.0) / (constants::G_HEIGHT * 1.0 - 1)));
                break;
            case conway:
                all_tiles[i] = rand() % 2;
                break;
            case rps: case rps_true:
                all_tiles[i] = rand() % constants::RPS_COLORS;
                break;
            case langton:
                all_tiles[i] = 1;
                break;
            case war:
                all_tiles[i] = rand() % constants::WAR_CARD_COUNT;
                break;
        }
        // std::cout << (int)std::round(100 * ( (y * 1.0) / (constants::G_HEIGHT * 1.0 - 1))) << " ";
        // std::cout << "x: " << pos[0] << "  y: " << pos[1] << "  i: " << i << "\n";
        // std::cout << id_from_pos( pos_from_id(i, pos ) ) << "  " << i << std::endl;
    }
}

void Grid::reset( SDL_Renderer* window_renderer ) {

    ant_pos[0] = constants::G_CENTER[0] * 1; 
    ant_pos[1] = constants::G_CENTER[1] * 1;

    for (int i = 0; i < constants::T_TILES; i ++) {
        do_update[i] = true;
        switch ( mode ) {
            case conway :
                all_tiles[i] = rand() % 2;
                break;
            case rps: case rps_true:
                all_tiles[i] = rand() % constants::RPS_COLORS;
                break;
            case langton:
                all_tiles[i] = 1;
                break;
            case war:
                all_tiles[i] = rand() % constants::WAR_CARD_COUNT;
                break;
        }
    }

    draw_all(window_renderer);
}

void Grid::reset( SDL_Renderer* window_renderer, int n_mode ) {
    mode = n_mode;
    reset( window_renderer );
}

void Grid::draw_all( SDL_Renderer* window_renderer ) {

    SDL_Color color;
    SDL_Rect rect;
    rect.h = constants::SQ_SIZE;
    rect.w = constants::SQ_SIZE;

    int x = 0, y = 0, t;

    double val;

    for (int i = 0; i < constants::T_TILES; i++) {
        if (do_update[i]) {
            t = all_tiles[i];
            // std::cout << t << " ";

            rect.x = x * constants::SQ_SIZE;
            rect.y = y * constants::SQ_SIZE;

            color = get_tile_color( i, t );

            SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, 255);
            SDL_RenderDrawRect(window_renderer, &rect);
            SDL_RenderFillRect(window_renderer, &rect);
            SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);
        }

        x++; 
        if ( x >= constants::G_WIDTH ) {
            x = 0;
            y++;
        } 

    }

    SDL_RenderPresent(window_renderer);

}

SDL_Color Grid::get_tile_color( int id, int tile_val ) {
    SDL_Color out_color;
    double val;

    switch (mode) {
        case gradient:
            val = (1.0 * tile_val) / 100;
            out_color = t_grad.get_mid_color(val);
            break;

        case conway: case langton:
            out_color.r = 255 * tile_val;
            out_color.g = 255 * tile_val;
            out_color.b = 255 * tile_val;
            break;

        case rps: case rps_true:
            out_color = colors::alt_colors[tile_val];
            // out_color = all_colors[tile_val];
            break;  

        case war:
            val = ( 1.0 * tile_val) / constants::WAR_CARD_COUNT;
            if (val > 1 or val < 0) std::cout << "issue: " << tile_val << "\n";
            out_color = t_grad.get_mid_color(val);
            break;
    }

    return out_color;
}

void Grid::draw_one( int x, int y, SDL_Renderer* window_renderer ) {
    SDL_Color color;
    SDL_Rect rect;
    rect.h = constants::SQ_SIZE;
    rect.w = constants::SQ_SIZE;

    rect.x = x * constants::SQ_SIZE;
    rect.y = y * constants::SQ_SIZE;

    int id = id_from_pos( x, y );
    int t = all_tiles[id];

    color = get_tile_color( id, t );

    SDL_SetRenderDrawColor(window_renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawRect(window_renderer, &rect);
    SDL_RenderFillRect(window_renderer, &rect);
    SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(window_renderer);
}

int Grid::id_from_pos( int x, int y ) {
    if (!is_in_bounds( x, y )) { return -1; }
    return (( constants::G_WIDTH - 1) * y) + x + y;
}

int Grid::id_from_pos( int pos[2] ) {
    if (!is_in_bounds( pos[0], pos[1] )) { return -1; }
    return ((constants::G_WIDTH - 1) * pos[1]) + pos[0] + pos[1];
}

int* Grid::pos_from_id( int id, int* pos ) {
    pos[0] = (id) % constants::G_WIDTH;
    pos[1] = ( ( (id) - pos[0] ) / constants::G_WIDTH );
    return pos;
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

int Grid::neighbors_with_value( int x, int y, int value, bool or_greater ) {
    int id, num = 0;

    for (int i = -1; i < 2; i ++) {
        for (int j = -1; j < 2; j ++) {
            id = id_from_pos( x + i, y + j );

            if ( !is_in_bounds(x + i, y + j) || (i == 0 && j == 0) ) continue;
            
            if ( or_greater ) {
                if ( copy_of_tiles[id] >= value ) num ++;
            } else {
                if ( copy_of_tiles[id] == value ) num ++;
            }
        }
    }
    return num;
}

// unused
int Grid::dist_from_center( int x, int y ) {
    // simply a distance function
    return std::sqrt( pow( ( x - ( constants::G_WIDTH / 2 ) ), 2 ) + pow( ( y - ( constants::G_HEIGHT / 2 ) ), 2 ) );
}

// --------- iterators ------------

void Grid::iterate_conway( int x, int y ) {
    int num_alive;
    int i = id_from_pos( x, y );

    num_alive = alive_neighbors(x, y);

    if (copy_of_tiles[1] == 0 && num_alive == 3) all_tiles[i] = 1;
    else if (num_alive < 2 || num_alive > 3) all_tiles[i] = 0;

    // manage positions
        
}
// // todo merge rps and rand rps
// void Grid::iterate_rps( int x, int y ) {
//     int i = id_from_pos( x, y );
//     int r, p, s;
//     int thresh = constants::RPS_THRESHHOLD;

//     r = neighbors_with_value(x, y, rock); // amount of rock neighbors
//     p = neighbors_with_value(x, y, paper);
//     s = neighbors_with_value(x, y, scissors);

//     // compares and replaces
//     if (copy_of_tiles[i] == rock && p > thresh) all_tiles[i] = paper;
//     else if (copy_of_tiles[i] == paper && s > thresh) all_tiles[i] = scissors;
//     else if (copy_of_tiles[i] == scissors && r > thresh) all_tiles[i] = rock;
// }


void Grid::iterate_rps( int x, int y ) {
    int i = id_from_pos( x, y );

    int beating_value = all_tiles[i] == constants::RPS_COLORS -1 ? 0 : all_tiles[i] + 1;
    int better_neighbors = neighbors_with_value( x, y, beating_value );

    if (better_neighbors > constants::RPS_THRESHHOLD) {
        all_tiles[i] = beating_value;
    }
}

void Grid::iterate_true_rps( int x, int y ) {
    //todo cleanup
    int i = id_from_pos( x, y );
    int beats_next = (constants::RPS_COLORS - 1) / 2;
    int best_winner[2] = {0, 0};

    for (int check_val = 1; check_val <= beats_next; check_val++) {
        int beating_value = (all_tiles[i] + check_val) % constants::RPS_COLORS; 
        int better_neighbors = neighbors_with_value(x, y, beating_value);
        if (better_neighbors >= best_winner[1]) {
            best_winner[0] = beating_value; 
            best_winner[1] = better_neighbors;
        }
    }

    if (best_winner[1] > constants::RPS_THRESHHOLD) {
        all_tiles[i] = best_winner[0];
    }
}

void Grid::iterate_rand_rps( int x, int y ) {
    int i = id_from_pos(x, y);
    int r, p, s, rand_val;
    int thresh = constants::RPS_THRESHHOLD;

    //todo replace neighbors with value with 3 filter rather than single - only do one loop each function call
    r = neighbors_with_value(x, y, 0);
    p = neighbors_with_value(x, y, 1);
    s = neighbors_with_value(x, y, 2);

    rand_val = rand() % 3;

    if (copy_of_tiles[i] == 0 && p > thresh + rand_val) all_tiles[i] = 1;
    else if (copy_of_tiles[i] == 1 && s > thresh + rand_val) all_tiles[i] = 2;
    else if (copy_of_tiles[i] == 2 && r > thresh + rand_val) all_tiles[i] = 0;
}

void Grid::iterate_langton( SDL_Renderer* window_renderer ) {
    
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

// void Grid::iterate_war( int x, int y ) {
//     int greater_neighbors;
//     int i = id_from_pos(x, y);

//     greater_neighbors = neighbors_with_value(x, y, copy_of_tiles[i], true);

//     if (greater_neighbors >= constants::WAR_THRESHHOLD and greater_neighbors <= constants::WAR_CAP) {
//         all_tiles[i] = rand() % constants::WAR_CARD_COUNT;
//     } 
// }

void Grid::iterate_war( int x, int y ) {
    int i = id_from_pos(x, y);
    int greater_neighbors = neighbors_with_value(x, y, all_tiles[i], true);
    
    
    if (greater_neighbors >= constants::WAR_THRESHHOLD and greater_neighbors <= constants::WAR_CAP) {
        all_tiles[i] = rand() % constants::WAR_CARD_COUNT;
    } else {
        all_tiles[i] = all_tiles[i] == 0 ? 0 : all_tiles[i] - 1; 
    }
}

void Grid::iterate( SDL_Renderer* window_renderer ) {
    int x = 0, y = 0;
    std::copy(std::begin(all_tiles), std::end(all_tiles), std::begin(copy_of_tiles));

    if (mode == langton) {
        iterate_langton(window_renderer);
        return;
    }
    // todo make foreach loop here
    for (int i = 0; i < constants::T_TILES; i++) {
        switch (mode) {
            case conway:
                iterate_conway( x, y );
                break;
            case rps:
                iterate_rps( x, y );
                break;
            case rps_true:
                iterate_true_rps( x, y );
                break;
            case war: 
                iterate_war( x, y );
                break;
        } 

        do_update[i] = all_tiles[i] != copy_of_tiles[i];

        x++;    
        if ( x >= constants::G_WIDTH ) {
            x = 0;
            y++;
        } 
    }
    draw_all(window_renderer);
}

// ----- Langtons ant methods -----

void Grid::turn_ant( int direction ) {
    ant_facing += direction;
    if (ant_facing == 4) ant_facing = 0;  
    else if (ant_facing == -1) ant_facing = 3; 
}

void Grid::move_ant() {

    ant_pos[0] += constants::DIRECTIONS[ant_facing][0];
    ant_pos[1] += constants::DIRECTIONS[ant_facing][1];

    if ( !is_in_bounds(ant_pos[0], ant_pos[1]) ) is_ant_dead = true; 

}