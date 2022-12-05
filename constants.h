#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
    constexpr int W_HEIGHT { 800 }; // window height
    constexpr int W_WIDTH { 800 }; // window width

    constexpr int SQ_SIZE { 8 }; // size of each tile, they should be squares 

    constexpr int G_HEIGHT { W_HEIGHT / SQ_SIZE }; // tiles in each column ~ grid height
    constexpr int G_WIDTH { W_WIDTH / SQ_SIZE }; // tiles in each row ~ grid width

    constexpr int T_TILES { G_HEIGHT * G_WIDTH }; // total number of tiles in the grid array

    constexpr int RPS_THRESHHOLD { 2 };

    constexpr int W_CENTER[2] { W_WIDTH / 2, W_HEIGHT / 2 };
    constexpr int G_CENTER[2] { G_WIDTH / 2, G_HEIGHT / 2 };

    constexpr int DIRECTIONS[4][2] {
            { 0, 1 },
            { 1, 0 },
            { 0, -1 },
            { -1, 0 },
        };
}

#endif