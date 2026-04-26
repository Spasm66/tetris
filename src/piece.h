#ifndef __PIECE__
#define __PIECE__
#include "struct.h"

typedef struct piece_s *piece;

piece   game_new_O(void);
piece   game_new_I(void);
piece   game_new_S(void);
piece   game_new_Z(void);
piece   game_new_L(void);
piece   game_new_J(void);
piece   game_new_T(void);
piece   game_new_random_piece(void);

#endif