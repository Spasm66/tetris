#include "struct.h"
#include "tetris.h"
#include "piece.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


tetris  new_tetris(int h, int w) {
    tetris  t;

    t = malloc(sizeof(struct tetris_s));
    t->matrice = malloc(h * sizeof(int*));
    for (int i = 0; i < HEIGHT; i++)
        t->matrice[i] = calloc(sizeof(int), w);
    return t;
}

void    clear_piece(tetris t, piece p) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (t->matrice[i][j] == PIECE)
                t->matrice[i][j] = EMPTY;
        }
    }
}

void    destroy_piece(piece p) {
    free(p->corp);
    free(p);
}

bool    hitting_floor(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int nx = p->pos->x + p->corp[x]->x + 1;
        int ny = p->pos->y + p->corp[x]->y;
        if (nx >= HEIGHT || t->matrice[nx][ny] == FLOOR){
            return true;
        }
    }
    return false;
}

bool    collapse_floor_wall(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int nx = p->pos->x + p->corp[x]->x;
        int ny = p->pos->y + p->corp[x]->y;
        if (ny <= 0 || ny >= WIDTH || nx >= HEIGHT ||t->matrice[nx][ny] == FLOOR){
            return true;
        }
    }
    return false;
}

void    fossilize(tetris t, piece p) {
    for (int x = 0; x < p->size; x++) {
        int i = p->pos->x + p->corp[x]->x;
        int j = p->pos->y + p->corp[x]->y;
        t->matrice[i][j] = FLOOR;
    }
    destroy_piece(p);
}

void    update_piece(tetris t, piece p) {
    int i;
    int j;
    clear_piece(t, p);
    for (int x = 0; x < p->size; x++) {
        i = p->pos->x + p->corp[x]->x;
        j = p->pos->y + p->corp[x]->y;
        t->matrice[i][j] = PIECE;
    }
}

bool    next(tetris t, piece p) {
    if (hitting_floor(t, p)) {
        update_piece(t, p);
        fossilize(t, p);
        return (false);
    }
    p->pos->x++;
    if (hitting_floor(t, p)) {
        update_piece(t, p);
        fossilize(t, p);
        return (false);
    }
    update_piece(t, p);
    return (true);
}

bool right(tetris t, piece p) {
    p->pos->y++;
    if (collapse_floor_wall(t, p)) {
        p->pos->y--;
        return (false);
    }
    update_piece(t, p);
    return (true);
}

bool left(tetris t, piece p) {
    p->pos->y--;
    if (collapse_floor_wall(t, p)) {
        p->pos->y++;
        return (false);
    }
    update_piece(t, p);
    return (true);
}

bool    turn(tetris t, piece p) {
    if (p->name == SQUARE)
        return true;
    int tmp;
    for (int x = 0; x < p->size; x++) {
        tmp = p->corp[x]->x;
        p->corp[x]->x = p->corp[x]->y;
        p->corp[x]->y = (-1) * tmp;
    }
    p->orientation = (p->orientation + 1) % 4;

    if (collapse_floor_wall(t, p)) {
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
    update_piece(t, p);
    return true;
}

void    print_tetris(tetris t) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (t->matrice[i][j])
            {
            case 0:
                printf(" ");
                break;
            case 1:
                printf("x");
                break;
            case 2:
                printf("o");
                break;

            default:
                break;
            }
        }
        printf("\n");
    }
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