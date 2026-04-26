#include "piece.h"
#include "struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

piece   game_new_O(void) {
    piece   p;
    position_s corp_data[] = {{0,0},{0,1}, {1, 0}, {1,1}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = O;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 0;
    p->pos->y = 5;
    return p;
}

piece   game_new_I(void) {
    piece   p;
    position_s corp_data[] = {{-1, 0},{0,0}, {1,0}, {2,0}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = I;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = 5;
    return p;
}

piece   game_new_S(void) {
    piece   p;
    position_s corp_data[] = {{1,-1}, {1,0}, {0,0}, {0,1}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = S;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = 5;
    return p;
}

piece   game_new_Z(void) {
    piece   p;
    position_s corp_data[] = {{0,-1}, {0,0}, {1,0}, {1,1}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = Z;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = 5;
    return p;
}

piece   game_new_L(void) {
    piece   p;
    position_s corp_data[] = {{-1, 0}, {0,0}, {1,0}, {1,1}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = L;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = 5;
    return p;
}

piece   game_new_J(void) {
    piece   p;
    position_s corp_data[] = {{-1, 0}, {0,0}, {1,0}, {1,-1}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = J;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = 5;
    return p;
}

piece   game_new_T(void) {
    piece   p;
    position_s corp_data[] = {{0, -1}, {0,0}, {1,0}, {0,1}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = T;
    p->orientation = NORTH;
    p->size = 4;
    for (int i = 0; i < p->size; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = 5;
    return p;
}

piece   game_new_random_piece(void) {
    int r;

    r = rand() % 7;
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

/*
int     main(void) {
    piece p;

    p = new_3line();
    printf("ok");
}
*/