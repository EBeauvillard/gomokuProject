#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "move.h"

void* next_player(int* current_player, void** players, int nb_players) {
  *current_player = (*current_player + 1) % nb_players;
  return players[*current_player];
}


struct col_move_t* add_move(struct col_move_t* m, struct col_move_t* moves, int* size_moves, int* nb_moves) {
  if (*nb_moves == *size_moves) {
    moves = realloc(moves, 2 * (*size_moves) * sizeof(*moves));
    (*size_moves) *= 2;
  }

  moves[*nb_moves] = *m;
  (*nb_moves)++;
  return moves;
}
