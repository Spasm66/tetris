#include "piece.h"
#include "tetris.h"
#include "struct.h"
#include "stdio.h"
#define WIDTH 10
#define HEIGHT 20

void    game_print_tetris(tetris t) {
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

    p = game_new_random_piece();
    t = game_new_tetris(WIDTH, HEIGHT);
    c = 'n';
    while (c != 'q') {
        switch (c)
        {
        case 'n':
            if (!game_next(t, p))
                p = game_new_random_piece();
            game_print_tetris(t);
            break;
        case 'r':
            game_right(t, p);
            game_print_tetris(t);
            break;
        case 'l':
            game_left(t, p);
            game_print_tetris(t);
            break;
        case 't':
            game_turn(t, p);
            game_print_tetris(t);
            break;
        default:
            break;
        }
        scanf("%c", &c);
    }
}