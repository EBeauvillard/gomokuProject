#ifndef _BITBOARD_PLAYER_H_
#define _BITBOARD_PLAYER_H_

#include <stddef.h>
#include "move.h"

/* Public functions */

/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name();

/* Returns a sequence of three moves for an opening
 * PARAM:
 * - size : the size of the board
 * PRECOND:
 * - size >= 5
 * RETURNS:
 * - an heap-allocated pointer to an array of three valid moves, that
     are consecutively BLACK, WHITE and BLACK.
 */
struct col_move_t* propose_opening(size_t size);

/* Acceptation of the opening
 * PARAM:
 * - size : the size of the board
 * - opening : a pointer to an array of three moves
 * PRECOND:
 * - size >= 5
 * - opening is an array of at least 3 elements
 * - the moves in opening form valid sequence of three moves BLACK,
     WHITE and BLACK
 * RETURNS:
 * - a boolean telling if the player accepts the opening
 */
int accept_opening(size_t size, const struct col_move_t* opening);

/* Player initialization
 * PARAM:
 * - size : the size of the board
 * - id: player ID,
 * PRECOND:
 * - size >= 5
 * - id is either BLACK or WHITE
 */
void initialize(size_t size, enum color_t id);

/* Computes next move
 * PARAM:
 * - previous_moves: ordered list of previous moves starting from the
 *   last move issued by the player if it exists, otherwise from the
 *   beginning of the game (opening moves are not considered as moves
 *   issued by a particular player, even if they have a color)
 * - n_moves: number of moves in previous_moves
 * PRECOND:
 * - previous_moves is an array of at least n_moves elements.
 * - previous_moves is an ordered list of previous moves starting from the last
 *   move of the player.
 * RETURNS:
 * - the next move for the player.
 */
struct move_t play(struct col_move_t const previous_moves[], size_t n_moves);

/* Announces the end of the game to the player, and cleans up the
   memory he may have been using.
 * POSTCOND:
 * - every allocation done during the calls to initialize and play
 *   functions must have been freed
 */
void finalize();

#endif // _BITBOARD_PLAYER_H_
