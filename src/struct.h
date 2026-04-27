#ifndef __STRUCT__
#define __STRUCT__

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
} direction;

typedef enum {
    EMPTY,
    PIECE,
    FLOOR,
} square;

typedef enum {
    O,
    I,
    S,
    Z,
    L,
    J,
    T,
} type;

typedef struct position_s {
    int x;
    int y;
} position_s;

typedef struct position_s* position;

typedef struct piece_s {
    type        name;
    direction   orientation;
    int         size;
    position  *corp;
    position  pos;
} piece_s;

typedef struct tetris_s {
    square  **matrice;
    int     w;
    int     h;
    int     level;
    int     score;
    int     del_row;
} tetris_s;

#endif