#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "move.h"
#include "bitboard.h"
#include "simple_strat.h"

void test()
{
  size_t size = 11;
  unsigned __int128 bitboardP = 0;
  print_bits(bitboardP, size);
  printf("\n");
  unsigned __int128 bitboardO = 0;
  print_bits(bitboardO, size);
  printf("\n");
  struct move_t res;
  for (int i = 0 ; i < size*size; i++)
  {
    if(is_won(bitboardP, size))
    {
      printf("player won\n");
      break;
    }
    if(is_won(bitboardO, size))
    {
      printf("opponent won\n");
      break;
    }
    if(i%2 == 0)
    {
      res = simple_strat(bitboardP, bitboardO, size);
      printf("result Player: {%zu,%zu}\n",res.row,res.col);
      bitboardP = operation_on_token(bitboardP, res.row, res.col, size, '+');
      print_bits(bitboardP, size);
      printf("\n");
      print_bits(bitboardO, size);
      printf("\n");
    }
    else
    {
      srand(time(NULL));
      size_t col = (rand() % size);
      size_t row = (rand() % size);
      while((!(is_empty_cell(bitboardP,row,col,size))) || (!(is_empty_cell(bitboardO,row,col,size))))
      {
          col = (rand() % size);
          row = (rand() % size);
      }
      bitboardO = operation_on_token(bitboardO, row, col, size, '+');
      printf("result Opponent: {%zu,%zu}\n", row, col);
      print_bits(bitboardP, size);
      printf("\n");
      print_bits(bitboardO, size);
      printf("\n");
    }
  }
  printf("nobody won !\n");
}


int main()
{
  printf("test (against random)\n");
  test();
}
