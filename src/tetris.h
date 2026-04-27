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
int     game_fossilize(tetris t, piece p);
void    game_update_piece(tetris t, piece p);
bool    game_score_updator(tetris t, int del_row);
bool    game_hitting_at_right(tetris t, piece p);
bool    game_hitting_at_left(tetris t, piece p);
bool    game_turn(tetris t, piece p);
int     game_get_score(tetris t);
void    game_set_score(tetris t, int s);
int     game_get_level(tetris t);
void    game_set_level(tetris t, int l);
#endif