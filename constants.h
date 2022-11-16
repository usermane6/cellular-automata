#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {
    constexpr int W_HEIGHT { 800 }; // window height
    constexpr int W_WIDTH { 800 }; // window width

    constexpr int SQ_SIZE { 10 }; // size of each tile, they should be squares 

    constexpr int G_HEIGHT { W_HEIGHT / SQ_SIZE }; // tiles in each column ~ grid height
    constexpr int G_WIDTH { W_WIDTH / SQ_SIZE }; // tiles in each row ~ grid width

    constexpr int T_TILES { G_HEIGHT * G_WIDTH }; // total number of tiles in the grid array
}

#endif