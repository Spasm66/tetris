#include <emscripten.h>
#include "src/tetris.h"
#include "src/piece.h"
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
tetris new_tetris(int h, int w) {
    return game_new_tetris(h, w);
}

EMSCRIPTEN_KEEPALIVE
void clear_piece(tetris t, piece p) {
    game_clear_piece(t, p);
}

EMSCRIPTEN_KEEPALIVE
void destroy_piece(piece p) {
    game_destroy_piece(p);
}

EMSCRIPTEN_KEEPALIVE
bool hitting_floor(tetris t, piece p) {
    return game_hitting_floor(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool collapse_floor_wall(tetris t, piece p) {
    return game_collapse_floor_wall(t, p);
}

EMSCRIPTEN_KEEPALIVE
void fossilize(tetris t, piece p) {
    game_fossilize(t, p);
}

EMSCRIPTEN_KEEPALIVE
void update_piece(tetris t, piece p) {
    game_update_piece(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool next(tetris t, piece p) {
    return game_next(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool right(tetris t, piece p) {
    return game_right(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool left(tetris t, piece p) {
    return game_left(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool turn(tetris t, piece p) {
    return game_turn(t, p);
}

EMSCRIPTEN_KEEPALIVE
piece new_random_piece(int r) {
    switch (r)
    {
    case 0:
        return (game_new_O());
        break;
    case 1:
        return (game_new_I());
        break;
    case 2:
        return (game_new_S());
        break;
     case 3:
        return (game_new_Z());
        break;
    case 4:
        return (game_new_L());
        break;
    case 5:
        return (game_new_J());
        break;
    case 6:
        return (game_new_T());
        break;
    
    default:
        break;
    }
    return (NULL);
}

EMSCRIPTEN_KEEPALIVE
square  get(tetris t, int x, int y) {
    return t->matrice[y][x];
}

EMSCRIPTEN_KEEPALIVE
void set(tetris t, square s, int x, int y) {
    t->matrice[y][x] = s;
}