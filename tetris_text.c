#include "piece.h"
#include "tetris.h"
#include "struct.h"
#include "stdio.h"

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

int main(void) {
    char    c;
    tetris  t;
    piece   p;

    p = new_3line();
    t = new_tetris(HEIGHT, WIDTH);
    c = 'n';
    while (c != 'q') {
        switch (c)
        {
        case 'n':
            if (!next(t, p))
                p = new_3line();
            print_tetris(t);
            break;
        case 'r':
            right(t, p);
            print_tetris(t);
            break;
        case 'l':
            left(t, p);
            print_tetris(t);
            break;
        case 't':
            turn(t, p);
            print_tetris(t);
            break;
        default:
            break;
        }
        scanf("%c", &c);
    }
}