#include "struct.h"
#include "tetris.h"
#include "piece.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


tetris  game_new_tetris(int w, int h) {
    tetris  t;

    t = malloc(sizeof(struct tetris_s));
    t->w = w;
    t->h = h;
    t->matrice = malloc(h * sizeof(int*));
    for (int i = 0; i < h; i++)
        t->matrice[i] = calloc(w, sizeof(int));
    return t;
}

void    game_clear_piece(tetris t, piece p) {
    for (int i = 0; i < t->h; i++) {
        for (int j = 0; j < t->w; j++) {
            if (t->matrice[i][j] == PIECE)
                t->matrice[i][j] = EMPTY;
        }
    }
}

void    game_destroy_piece(piece p) {
    for (int i = 0; i < p->size; i++)
        free(p->corp[i]);   // ← free chaque position
    free(p->corp);
    free(p->pos);           // ← manquait aussi
    free(p);
}

bool    game_hitting_floor(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int nx = p->pos->x + p->corp[x]->x + 1;
        int ny = p->pos->y + p->corp[x]->y;
        if (nx >= t->h || t->matrice[nx][ny] == FLOOR){
            return true;
        }
    }
    return false;
}

bool    game_collapse_floor_wall(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int nx = p->pos->x + p->corp[x]->x;
        int ny = p->pos->y + p->corp[x]->y;
        if (ny <= 0 || ny >= t->w || nx < 0 || nx >= t->h ||t->matrice[nx][ny] == FLOOR){
            return true;
        }
    }
    return false;
}

void    game_fossilize(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int i = p->pos->x + p->corp[x]->x;
        int j = p->pos->y + p->corp[x]->y;
        t->matrice[i][j] = FLOOR;
    }
    game_destroy_piece(p);
}

void    game_update_piece(tetris t, piece p) {
    int i;
    int j;
    game_clear_piece(t, p);
    for (int x = 0; x < p->size; x++) {
        i = p->pos->x + p->corp[x]->x;
        j = p->pos->y + p->corp[x]->y;
        t->matrice[i][j] = PIECE;
    }
}

bool    game_next(tetris t, piece p) {
    if (game_hitting_floor(t, p)) {
        game_update_piece(t, p);
        game_fossilize(t, p);
        return (false);
    }
    p->pos->x++;
    if (game_hitting_floor(t, p)) {
        game_update_piece(t, p);
        game_fossilize(t, p);
        return (false);
    }
    game_update_piece(t, p);
    return (true);
}

bool game_right(tetris t, piece p) {
    p->pos->y++;
    if (game_collapse_floor_wall(t, p)) {
        p->pos->y--;
        return (false);
    }
    game_update_piece(t, p);
    return (true);
}

bool game_left(tetris t, piece p) {
    p->pos->y--;
    if (game_collapse_floor_wall(t, p)) {
        p->pos->y++;
        return (false);
    }
    game_update_piece(t, p);
    return (true);
}

bool    game_turn(tetris t, piece p) {
    if (p->name == O)
        return true;
    int tmp;
    for (int x = 0; x < p->size; x++) {
        tmp = p->corp[x]->x;
        p->corp[x]->x = p->corp[x]->y;
        p->corp[x]->y = (-1) * tmp;
    }
    p->orientation = (p->orientation + 1) % 4;

    if (game_collapse_floor_wall(t, p)) {
        for (int i = 0; i < 3; i++) {
            for (int x = 0; x < p->size; x++) {
                tmp = p->corp[x]->x;
                p->corp[x]->x = p->corp[x]->y;
                p->corp[x]->y = (-1) * tmp;
            }
        }
        p->orientation = (p->orientation + 3) % 4;
        return false;
    }
    game_update_piece(t, p);
    return true;
}

/*
int     main(void) {
    piece   p;
    tetris  t;

    p = new_3line();
    t = new_tetris(HEIGHT, WIDTH);
    next(p);
    update_piece(t, p);
    print_tetris(t);
    right(p);
    update_piece(t, p);
    print_tetris(t);
}
*/