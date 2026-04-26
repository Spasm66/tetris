#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"

game game_load(char *filename) {
    uint nb_cols, nb_rows;
    int wrapped;
    char l;
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("erreur ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%u %u %d \n", &nb_rows, &nb_cols, &wrapped);

    uint *expected_tr = malloc(sizeof(uint) * nb_rows);
    uint *expected_tc = malloc(sizeof(uint) * nb_cols);
    square *s = malloc(sizeof(square) * nb_rows * nb_cols);

    for (uint i = 0; i < nb_rows; i++) fscanf(f, "%u ", &expected_tr[i]);

    for (uint j = 0; j < nb_cols; j++) fscanf(f, "%u ", &expected_tc[j]);

    uint s_cur = 0;

    for (uint i = 0; i < nb_rows; i++) {
        for (uint j = 0; j < nb_cols; j++) {
            fscanf(f, " %c", &l);
            if (l == 'X')
                s[s_cur++] = TREE;
            else if (l == 'G')
                s[s_cur++] = GRASS;
            else if (l == 'T')
                s[s_cur++] = TENT;
            else if (l == 'B')
                s[s_cur++] = BIGTREE;
            else if (l == 'E')
                s[s_cur++] = EMPTY;
            else {
                fprintf(stderr, "caractere invalide");
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(f);
    game g =
        game_new_ext(nb_rows, nb_cols, s, expected_tr, expected_tc, wrapped);
    free(s);
    free(expected_tr);
    free(expected_tc);
    return g;
}

void game_save(cgame g, char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char tab[] = {'E', 'X', 'T', 'G', 'B'};
    int wrapped;
    if (game_is_wrapping(g) == true) {
        wrapped = 1;
    } else {
        wrapped = 0;
    }
    fprintf(f, "%d %d %d \n", g->nb_rows, g->nb_cols, wrapped);

    for (int i = 0; i < g->nb_rows; i++) {
        fprintf(f, "%d ", game_get_expected_nb_tents_row(g, i));
    }
    fprintf(f, "\n");
    for (int j = 0; j < g->nb_cols; j++) {
        fprintf(f, "%d ", game_get_expected_nb_tents_col(g, j));
    }
    fprintf(f, "\n");
    // grille
    for (int i = 0; i < g->nb_rows; i++) {
        for (int j = 0; j < g->nb_cols; j++) {
            fprintf(f, "%c ", tab[game_get_square(g, i, j)]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return;
}


/*                                RANDOM                                      */
/* ************************************************************************** */

static int opposite_direction(direction d)
{
  switch (d) {
    case UP:
      return DOWN;
    case DOWN:
      return UP;
    case LEFT:
      return RIGHT;
    case RIGHT:
      return LEFT;
    case UP_LEFT:
      return DOWN_RIGHT;
    case UP_RIGHT:
      return DOWN_LEFT;
    case DOWN_LEFT:
      return UP_RIGHT;
    case DOWN_RIGHT:
      return UP_LEFT;
    case HERE:
      return HERE;
  }
  return -1;  // to avoid warning
}

/* ************************************************************************** */

static bool try_to_place_tree(game g, bool big)
{
  uint nb_rows = game_nb_rows(g);
  uint nb_cols = game_nb_cols(g);
  uint i_tree = rand() % nb_rows;
  uint j_tree = rand() % nb_cols;
  if (game_get_square(g, i_tree, j_tree) != EMPTY) return false;  // already occupied
  direction dir = (rand() % 4) + 1;                               // UP,DOWN,LEFT,RIGHT
  uint i_tent, j_tent;
  bool ok = game_get_adjacent_square(g, i_tree, j_tree, dir, &i_tent, &j_tent);
  if (!ok) return false;                                           // out of bounds
  if (game_get_square(g, i_tent, j_tent) != EMPTY) return false;   // already occupied
  if (game_is_neigh(g, i_tent, j_tent, TENT, true)) return false;  // adjacent to another tent

  // for big tree, check square on opposite side for the second tent
  uint i_tent2, j_tent2;
  if (big) {
    direction opposite_dir = opposite_direction(dir);
    bool ok2 = game_get_adjacent_square(g, i_tree, j_tree, opposite_dir, &i_tent2, &j_tent2);
    if (!ok2) return false;
    if (game_get_square(g, i_tent2, j_tent2) != EMPTY) return false;   // already occupied
    if (game_is_neigh(g, i_tent2, j_tent2, TENT, true)) return false;  // adjacent to another tent
  }

  // place tree & first tent
  game_set_square(g, i_tree, j_tree, TREE);
  game_set_expected_nb_tents_row(g, i_tent, game_get_expected_nb_tents_row(g, i_tent) + 1);
  game_set_expected_nb_tents_col(g, j_tent, game_get_expected_nb_tents_col(g, j_tent) + 1);
  game_set_square(g, i_tent, j_tent, TENT);

  // place big tree & second tent
  if (big) {
    game_set_square(g, i_tree, j_tree, BIGTREE);
    game_set_expected_nb_tents_row(g, i_tent2, game_get_expected_nb_tents_row(g, i_tent2) + 1);
    game_set_expected_nb_tents_col(g, j_tent2, game_get_expected_nb_tents_col(g, j_tent2) + 1);
    game_set_square(g, i_tent2, j_tent2, TENT);
  }

  return true;
}

/* ************************************************************************** */

game game_random(uint nb_rows, uint nb_cols, bool wrapping, uint nb_trees, uint nb_bigtrees,
                 bool solution)
{
  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping);
  assert(g);

  // try to place big trees first
  int num_bigtree = 0;
  int nb_bigtree_tries = 0;
  while (num_bigtree < nb_bigtrees) {
    if (nb_bigtree_tries >= 10 * nb_bigtrees) break;  // avoid infinite loop
    nb_bigtree_tries++;
    if (try_to_place_tree(g, true)) num_bigtree++;
  }

  printf("Placed %d big trees (requested %d) after %d tries\n", num_bigtree, nb_bigtrees,
         nb_bigtree_tries);

  // then try to place trees
  int num_tree = 0;
  int nb_tree_tries = 0;
  while (num_tree < nb_trees) {
    if (nb_tree_tries >= 10 * nb_trees) break;  // avoid infinite loop
    nb_tree_tries++;
    if (try_to_place_tree(g, false)) num_tree++;
  }

  printf("Placed %d trees (requested %d) after %d tries\n", num_tree, nb_trees, nb_tree_tries);

  game_fill_grass(g);
  assert(game_won(g));
  if (!solution) game_restart(g);
  return g;
}


/*
void solve2(game g, uint nb_cols, uint nb_rows, int i, int j, bool *found) {
    if (*found) return;  // stop deja trouver la solution

    if (i == nb_rows) {  // fin de grille
        if (game_won(g)) {
            *found = true;
        }

        return;
    }
    if (j == nb_cols) {  // fin de ligne
        solve(g, nb_cols, nb_rows, i + 1, 0, found);
        return;
    }
    // si cest un arbre passe
    if (game_get_square(g, i, j) == TREE) {
        solve(g, nb_cols, nb_rows, i, j + 1, found);
        return;
    }
    // essaye tente
    if (game_check_move(g, i, j, TENT) && !game_nb_neigh(g, i, j, TENT, true) &&
        game_nb_neigh(g, i, j, TREE, false) &&
        game_get_current_nb_tents_col(g, j) + 1 <=
            game_get_expected_nb_tents_col(g, j) &&
        game_get_current_nb_tents_row(g, i) + 1 <=
            game_get_expected_nb_tents_row(g, i)) {
        game_set_square(g, i, j, TENT);
        solve(g, nb_cols, nb_rows, i, j + 1, found);
        if (*found) return;
        game_set_square(g, i, j, EMPTY);
    }

    // essaye empty
    game_set_square(g, i, j, EMPTY);
    solve(g, nb_cols, nb_rows, i, j + 1, found);
}
*/

bool solve_rec(game g, uint depth, uint **trees)
{

    if (game_won(g))
        return true;

    else
    {
        // pour la lisibilité
        uint i = trees[depth][0];
        uint j = trees[depth][1];

        if(     i + 1 < g->nb_rows && 
                game_get_current_nb_tents_row(g, i + 1) < game_get_expected_nb_tents_row(g, i + 1) &&
                game_get_current_nb_tents_col(g, j) < game_get_expected_nb_tents_col(g, j) &&
                game_get_square(g, i + 1, j) == EMPTY && 
                game_check_move(g, i + 1, j, TENT) &&
                !game_is_neigh(g, i + 1, j, TENT, true))

        {
            game_set_square(g, i + 1, j, TENT);
            if (depth)
            {
                if (!solve_rec(g, depth - 1, trees))
                    game_set_square(g, i + 1, j, EMPTY);
                
                else
                    return true;
            }
            else
            {
                if (!game_won(g))
                    game_set_square(g, i + 1, j, EMPTY);
                else
                    return true;
            }
        }

        if (i &&
            game_get_current_nb_tents_row(g, i - 1) < game_get_expected_nb_tents_row(g, i - 1) &&
            game_get_current_nb_tents_col(g, j) < game_get_expected_nb_tents_col(g, j) &&
            game_get_square(g, i - 1, j) == EMPTY && 
            game_check_move(g, i - 1, j, TENT) &&
            !game_is_neigh(g, i - 1, j, TENT, true))

        {
            game_set_square(g, i - 1, j, TENT);
            if (depth)
            {
                if (!solve_rec(g, depth - 1, trees))
                    game_set_square(g, i - 1, j, EMPTY);
                
                else
                    return true;
            }
            else
            {
                if (!game_won(g))
                    game_set_square(g, i - 1, j, EMPTY);
                else
                    return true;
            }            
        }

        if (j + 1 < g->nb_cols && 
            game_get_current_nb_tents_row(g, i) < game_get_expected_nb_tents_row(g, i) &&
            game_get_current_nb_tents_col(g, j + 1) < game_get_expected_nb_tents_col(g, j + 1) &&
            game_get_square(g, i, j + 1) == EMPTY && 
            game_check_move(g, i, j + 1, TENT) &&
            !game_is_neigh(g, i, j + 1, TENT, true))
        {
            game_set_square(g, i, j + 1, TENT);
            if (depth)
            {
                if (!solve_rec(g, depth - 1, trees))
                    game_set_square(g, i, j + 1, EMPTY);
                
                else
                    return true;
            }
            else
            {
                if (!game_won(g))
                    game_set_square(g, i, j + 1, EMPTY);
                else
                    return true;
            }
            
        }

        if (j &&
            game_get_current_nb_tents_row(g, i) < game_get_expected_nb_tents_row(g, i) &&
            game_get_current_nb_tents_col(g, j - 1) < game_get_expected_nb_tents_col(g, j - 1) &&
            game_get_square(g, i, j - 1) == EMPTY && 
            game_check_move(g, i, j - 1, TENT) &&
            !game_is_neigh(g, i, j - 1, TENT, true))
        {
            game_set_square(g, i, j - 1, TENT);
            if (depth)
            {
                if (!solve_rec(g, depth - 1, trees))
                    game_set_square(g, i, j - 1, EMPTY);
                
                else
                    return true;
            }
            else
            {
                if (!game_won(g))
                    game_set_square(g, i, j - 1, EMPTY);
                else
                    return true;
            }
        }
    }
    if (!depth)
        return game_won(g);
    else
        return solve_rec(g, depth - 1, trees);
}


void solve(game g, bool *found)
{
    uint nb_trees = game_get_expected_nb_tents_all(g);
    uint nb_found = 0;
    uint **trees = malloc(sizeof(uint *) * nb_trees);
    for (uint i = 0; i < nb_trees; i++)
        trees[i] = malloc(sizeof(uint) * 2);
    
    for (uint i = 0; i < g->nb_rows; i++)
    {
        for(uint j = 0; j < g->nb_cols; j++)
        {
            if (SQUARE(g, i, j) == TREE)
            {
                trees[nb_found][0] = i;
                trees[nb_found++][1] = j;
            }
        }
    }
    if (!nb_found)
        *found = false;
    else
        solve_rec(g, nb_found - 1, trees);
    for (uint i = 0; i < nb_trees; i++)
        free(trees[i]);
    free(trees);
}


bool game_solve(game g) {
    bool found = true;
    //solve(g, g->nb_cols, g->nb_cols, 0, 0, &found);
    solve(g, &found);
    return found;
}

void nb_solutions(game g, uint nb_cols, uint nb_rows, int i, int j, uint *cpt) {
    if (i == nb_rows) {  // fin de grille
        if (game_won(g)) {
            (*cpt)++;
        }
        return;
    }
    if (j == nb_cols) {  // fin de ligne
        nb_solutions(g, nb_cols, nb_rows, i + 1, 0, cpt);
        return;
    }
    // si cest un arbre passe
    if (game_get_square(g, i, j) == TREE) {
        nb_solutions(g, nb_cols, nb_rows, i, j + 1, cpt);
        return;
    }
    // essaye tente
    if (game_check_move(g, i, j, TENT) && !game_nb_neigh(g, i, j, TENT, true) &&
        game_nb_neigh(g, i, j, TREE, false) &&
        game_get_current_nb_tents_col(g, j) + 1 <=
            game_get_expected_nb_tents_col(g, j)) {
        game_set_square(g, i, j, TENT);
        nb_solutions(g, nb_cols, nb_rows, i, j + 1, cpt);
    }

    // essaye empty
    game_set_square(g, i, j, EMPTY);
    nb_solutions(g, nb_cols, nb_rows, i, j + 1, cpt);
}

uint game_nb_solutions(cgame g) {
    game g1 = game_copy(g);
    uint nb_rows = g1->nb_rows;
    uint nb_cols = g1->nb_cols;
    uint cpt = 0;

    nb_solutions(g1, nb_cols, nb_rows, 0, 0, &cpt);
    game_delete(g1);
    return cpt;
}