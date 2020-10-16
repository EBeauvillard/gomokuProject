#ifndef _TOOLS_H_
#define _TOOLS_H_

#define DEFAULT_SIZE 11
#define DEFAULT_NB_PLAYERS 2
#define OPENING_SIZE 3
#define MIN_SIZE 5
#define MAX_SIZE 11

/* Changing current player to the next one
 * PARAM:
 * - current_player : a pointer to an int representing the current player
 * - players : a pointer to an array of players' handlers
 * - nb_players : the number of players
 * PRECOND:
 * - players is an array of nb_players elements
 */
void* next_player(int* current_player, void** players, int nb_players);

/* Add a move to the list of moves
 * PARAM:
 * - m : move to add
 * - moves : ordered list of moves
 * - size_moves: size allocated of the array moves
 * - n_moves: number of moves in moves
 * RETURNS:
 * - the updated list of moves
 */
struct col_move_t* add_move(struct col_move_t* m, struct col_move_t* moves, int* size_moves, int* nb_moves);

#endif // _TOOLS_H_
