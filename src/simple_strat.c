#include <stdio.h>

#include "move.h"
#include "bitboard.h"
#include "simple_strat.h"

//Plays by putting each token besides each other (if the cell is not full)
struct move_t simple_strat(unsigned __int128 bitboardP, unsigned __int128 bitboardO, size_t size)
{
  struct move_t move = {0,0};
  for (size_t row = 0; row < size; row ++)
  {
    for (size_t col = 0; col < size; col ++)
    {
      if((is_empty_cell(bitboardP,row,col,size)) && (is_empty_cell(bitboardO,row,col,size)))
      {
        move.row = row;
        move.col = col;
        return move;
      }
    }
  }
  return move;
}
