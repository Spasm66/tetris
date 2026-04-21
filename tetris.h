#ifndef __TETRIS__
#define __TETRICE__
#include "struct.h"
#include "piece.h"
#include <stdbool.h>

typedef struct tetris_s *tetris;

tetris  new_tetris(int h, int w);
void    clear_piece(tetris t, piece p);
void    destroy_piece(piece p);
bool    hitting_floor(tetris t, piece p);
bool    collapse_floor_wall(tetris t, piece p);
void    fossilize(tetris t, piece p);
void    update_piece(tetris t, piece p);
bool    next(tetris t, piece p);
bool    right(tetris t, piece p);
bool    left(tetris t, piece p);
bool    turn(tetris t, piece p);
#endif