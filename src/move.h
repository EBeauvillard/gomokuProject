#ifndef _BITBOARD_MOVE_H_
#define _BITBOARD_MOVE_H_

#include <stddef.h>

/* Players */
enum color_t { BLACK=0, WHITE=1, RED=2, BLUE=3 };

/* Positions */
struct move_t { size_t row,col; };
/* Position (0,0) is on the upper-left corner,
   Position (0,1) is on the right of this corner,
   Position (1,0) is just below this corner */

struct col_move_t {
  struct move_t m;
  enum color_t c;
};

#endif // _BITBOARD_MOVE_H_
