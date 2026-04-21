#include "piece.h"
#include "struct.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

piece   new_3line(void) {
    piece   p;
    position_s corp_data[] = {{-1, 0},{0,0}, {1,0}};

    p = malloc(sizeof(struct piece_s));
    p->corp = malloc(sizeof(corp_data));
    p->name = THREELINE;
    p->orientation = NORTH;
    for (int i = 0; i < 3; i++) {
        p->corp[i] = malloc(sizeof(position_s));
        p->corp[i]->x = corp_data[i].x;
        p->corp[i]->y = corp_data[i].y;
    }
    p->size = 3;
    p->pos = malloc(sizeof(position_s));
    p->pos->x = 1;
    p->pos->y = WIDTH / 2;
    return p;
}



/*
int     main(void) {
    piece p;

    p = new_3line();
    printf("ok");
}
*/