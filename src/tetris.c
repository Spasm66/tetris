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
    t->score = 0;
    t->level = 1;
    t->del_row = 0;
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
        if (nx >= t->h || ny < 0 || ny >= t->w)
            return true;
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
        if (ny < 0 || ny >= t->w || nx < 0 || nx >= t->h ||t->matrice[nx][ny] == FLOOR){
            return true;
        }
    }
    return false;
}

int     game_check_row(tetris t) {
    int sum;

    for (int i = 0; i < t->h; i++) {
        sum = 0;
        for (int j = 0; j < t->w; j++)
            sum += t->matrice[i][j];
        if (sum == t->w * 2)
            return (i);
    }
    return (-1);
}

void    game_remove_row(tetris t, int row) {
    for (int i = row; i >= 1; i--)
        t->matrice[i] = t->matrice[i-1];
}

int     game_get_score(tetris t) {
    return (t->score);
}

void    game_set_score(tetris t, int s) {
        t->score = s;
}

int     game_get_level(tetris t) {
    return (t->level);
}

void    game_set_level(tetris t, int l) {
        t->level = l;
}

int     game_fossilize(tetris t, piece p) {
    int row;
    int nb;

    for (int x = 0; x < p->size; x++) {
        int i = p->pos->x + p->corp[x]->x;
        int j = p->pos->y + p->corp[x]->y;
        t->matrice[i][j] = FLOOR;
    }
    row = game_check_row(t);
    nb = 0;
    while (row != -1) {
        game_remove_row(t, row);
        row = game_check_row(t);
        nb += 1;
    }
    game_destroy_piece(p);
    return (nb);
}

void    game_update_piece(tetris t, piece p) {
    int i;
    int j;
    game_clear_piece(t, p);
    for (int x = 0; x < p->size; x++) {
        i = p->pos->x + p->corp[x]->x;
        j = p->pos->y + p->corp[x]->y;
        if (i >= 0 && i < t->h && j >= 0 && j < t->w)
            t->matrice[i][j] = PIECE;
    }
}

bool    game_score_updator(tetris t, int del_row) {
    return (false);
}

bool game_hitting_at_right(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int ny = p->pos->y + p->corp[x]->y;
        int nx = p->pos->x + p->corp[x]->x;
        if (ny+1 >= t->w || t->matrice[nx][ny+1] == FLOOR){
            return true;
        }
    }
    return false;
}

bool game_hitting_at_left(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int ny = p->pos->y + p->corp[x]->y;
        int nx = p->pos->x + p->corp[x]->x;
        if (ny <= 0 || t->matrice[nx][ny-1] == FLOOR){
            return true;
        }
    }
    return false;
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