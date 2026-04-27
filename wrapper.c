#include <emscripten.h>
#include "src/tetris.h"
#include "src/piece.h"
#include <stdbool.h>
#include <stdlib.h>

EMSCRIPTEN_KEEPALIVE
tetris new_tetris(int w, int h) {
    return game_new_tetris(w, h);
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
bool hitting_at_right(tetris t, piece p) {
    return game_hitting_at_right(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool hitting_at_left(tetris t, piece p) {
    return game_hitting_at_left(t, p);
}

EMSCRIPTEN_KEEPALIVE
int fossilize(tetris t, piece p) {
    return game_fossilize(t, p);
}

EMSCRIPTEN_KEEPALIVE
void update_piece(tetris t, piece p) {
    game_update_piece(t, p);
}


EMSCRIPTEN_KEEPALIVE
bool collapse_floor_wall(tetris t, piece p) {
    return game_collapse_floor_wall(t, p);
}

EMSCRIPTEN_KEEPALIVE
bool score_updator(tetris t, int del_row) {
    return game_score_updator(t, del_row);
}

EMSCRIPTEN_KEEPALIVE
int get_score(tetris t) {
    return game_get_score(t);
}

EMSCRIPTEN_KEEPALIVE
void set_score(tetris t, int s) {
    game_set_score(t, s);
}

EMSCRIPTEN_KEEPALIVE
int get_level(tetris t) {
    return game_get_level(t);
}

EMSCRIPTEN_KEEPALIVE
void set_level(tetris t, int l) {
    game_set_level(t, l);
}

EMSCRIPTEN_KEEPALIVE
square get(tetris t, int x, int y) {
    return t->matrice[y][x];
}

EMSCRIPTEN_KEEPALIVE
void set(tetris t, square s, int x, int y) {
    t->matrice[y][x] = s;
}

EMSCRIPTEN_KEEPALIVE
void next(piece p) {
    game_next(p);
}

EMSCRIPTEN_KEEPALIVE
void right(piece p) {
    game_right(p);
}

EMSCRIPTEN_KEEPALIVE
void left(piece p) {
    game_left(p);
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
bool turn(tetris t, piece p) {
    return game_turn(t, p);
}

EMSCRIPTEN_KEEPALIVE
piece new_O(void) { return game_new_O(); }

EMSCRIPTEN_KEEPALIVE
piece new_I(void) { return game_new_I(); }

EMSCRIPTEN_KEEPALIVE
piece new_S(void) { return game_new_S(); }

EMSCRIPTEN_KEEPALIVE
piece new_Z(void) { return game_new_Z(); }

EMSCRIPTEN_KEEPALIVE
piece new_L(void) { return game_new_L(); }

EMSCRIPTEN_KEEPALIVE
piece new_J(void) { return game_new_J(); }

EMSCRIPTEN_KEEPALIVE
piece new_T(void) { return game_new_T(); }