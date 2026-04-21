#ifndef __STRUCT__
#define __STRUCT__
#define WIDTH 20
#define HEIGHT 15

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
    SQUARE,
    THREELINE,
    FOURLINE,
    L,
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
} tetris_s;

#endif