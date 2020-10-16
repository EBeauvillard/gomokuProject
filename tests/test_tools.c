#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "move.h"
#include "tests.h"

//Tests "next_player" function
void tests_next_player() {
  int current_player = 0;
  int nb_players = 4;
  void* players[] = { (void*) 1, (void*) 2, (void*) 3, (void*) 4 };

  printf("**** Tests next_player ****\n");
  for (int i=1; i<=nb_players; i++) {
    display_test("  - Test next player for 4 players", next_player(&current_player, players, nb_players) == players[i%nb_players]);
  }
}

//Tests "add_move" function
void tests_add_move() {
  struct col_move_t* moves;
  moves = malloc(sizeof(*moves));
  int size_moves = 1;
  int nb_moves = 0;

  struct col_move_t m1 = { {0, 0}, 0 };
  struct col_move_t m2 = { {1, 1}, 1 };

  printf("**** Tests add_move ****\n");
  moves = add_move(&m1, moves, &size_moves, &nb_moves);
  display_test("  - Test incrementation nb_moves", nb_moves == 1);
  display_test("  - Test added move corresponding (row)", m1.m.row == moves[0].m.row);
  display_test("  - Test added move corresponding (col)", m1.m.col == moves[0].m.col);
  display_test("  - Test added move corresponding (color)", m1.c == moves[0].c);
  moves = add_move(&m2, moves, &size_moves, &nb_moves);
  display_test("  - Test incrementation size_moves", size_moves == 1*2);

  free(moves);
}


int main() {
	tests_next_player();
  tests_add_move();
	return 0;
}
