#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL2/SDL.h>
#include "gradient.h" 

namespace constants {
    constexpr int W_HEIGHT { 900 }; // window height in pixels
    constexpr int W_WIDTH { 900 }; // window width in pixels

    constexpr int SQ_SIZE { 2 }; // size of each tile, they should be squares 

    constexpr int G_HEIGHT { W_HEIGHT / SQ_SIZE }; // tiles in each column ~ grid height
    constexpr int G_WIDTH { W_WIDTH / SQ_SIZE }; // tiles in each row ~ grid width

    constexpr int T_TILES { G_HEIGHT * G_WIDTH }; // total number of tiles in the grid array

    constexpr int RPS_THRESHHOLD { 2 }; // amount of rps losses required to change color
    constexpr int RPS_COLORS { 5 };

    constexpr int WAR_THRESHHOLD { 5 }; // amount of war losses 
    constexpr int WAR_CAP { 6 };
    constexpr int WAR_CARD_COUNT { 100 }; // amount of different cards in a "deck" of cards

    constexpr int W_CENTER[2] { W_WIDTH / 2, W_HEIGHT / 2 }; // center in terms of pixels, window center
    constexpr int G_CENTER[2] { G_WIDTH / 2, G_HEIGHT / 2 }; // center in terms of grid tiles, grid center

    constexpr int DIRECTIONS[4][2] {
            { 0, 1 },
            { 1, 0 },
            { 0, -1 },
            { -1, 0 },
        }; 

    constexpr int  FONT_SIZE = 20;
}

namespace colors {
    const SDL_Color t_color1 = {255, 3, 192};
    const SDL_Color t_color2 = {20, 0, 100};

    const SDL_Color rps_colors[10] = {
        {250, 218, 102},
        {100, 54, 156},
        {196, 149, 61},
        {105, 67, 117},
        {186, 35, 156},
        {66, 2, 79},
        {49, 23, 179},
        {71, 179, 162},
        {28, 230, 149},
        {242, 148, 61},
    };

    const SDL_Color alt_colors[6] = {
        {255, 255, 255},
        {215, 36, 131},
        {191, 192, 192},
        {45, 49, 66},
        {239, 131, 84},
        {79, 93, 117},
    };
}

#endif