#ifndef __TETRIS__
#define __TETRIS__
#include "struct.h"
#include "piece.h"
#include <stdbool.h>

typedef struct tetris_s *tetris;

tetris  game_new_tetris(int w, int h);
void    game_clear_piece(tetris t, piece p);
void    game_destroy_piece(piece p);
bool    game_hitting_floor(tetris t, piece p);
bool    game_collapse_floor_wall(tetris t, piece p);
void    game_fossilize(tetris t, piece p);
void    game_update_piece(tetris t, piece p);
bool    game_next(tetris t, piece p);
bool    game_right(tetris t, piece p);
bool    game_left(tetris t, piece p);
bool    game_turn(tetris t, piece p);
#endif