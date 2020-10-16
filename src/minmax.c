#include <stdio.h>

#include "move.h"
#include "bitboard.h"
#include "minmax.h"

#define INFINITY 1000

//struct for the possible moves to do
struct p_moves{
  struct move_t l_moves[11*11]; //list of possible moves
  int n_of_moves; //number of possible moves
};

//struct to get both the value and the position of a token for the minmax
struct node{
  struct move_t mv_node; //position of the move
  int value; //value of the move
};

//counts the number of tokens around row/col spot ; used i <= row instead of row-i >= 0 because it's a size_t (and in first place to avoid bugs)
int nb_series(const unsigned __int128 bitboard, size_t row, size_t col, size_t size)
{
  int value = 0;

  //booleans set to true
  char r1=1, r2=1, c1=1, c2=1, d1=1, d2=1, d3=1, d4=1;

  for (size_t i = 0; i < 5; i++)
  {
    //counts for the row right and left
    if((row + i < size) && !(is_empty_cell(bitboard,row + i,col,size)) && r1)
    {
      value++;
    }
    else
    {
      r1 = 0;
    }
    if((i <= row) && !(is_empty_cell(bitboard,row - i,col,size)) && r2)
    {
      value++;
    }
    else
    {
      r2 = 0;
    }

    //counts for the column down and up
    if((col + i < size) && !(is_empty_cell(bitboard,row,col + i,size)) && c1)
    {
      value++;
    }
    else
    {
      c1 = 0;
    }
    if((i <= col) && !(is_empty_cell(bitboard,row,col - i,size)) && c2)
    {
      value++;
    }
    else
    {
      c2 = 0;
    }

    //counts for the diagonal top to bottom (from right to left)
    if((i <= col) && (i <= row) && !(is_empty_cell(bitboard,row - i,col - i,size)) && d1)
    {
      value++;
    }
    else
    {
      d1 = 0;
    }
    if((col + i < size) && (row + i < size) && !(is_empty_cell(bitboard,row + i,col + i,size)) && d2)
    {
      value++;
    }
    else
    {
      d2 = 0;
    }

    //counts for the diagonal bottom to top (from right to left)
    if((i <= col) && (row + i < size) && !(is_empty_cell(bitboard,row + i,col - i,size)) && d3)
    {
      value++;
    }
    else
    {
      d3 = 0;
    }
    if((i <= row) && (col + i < size) && !(is_empty_cell(bitboard,row - i,col + i,size)) && d4)
    {
      value++;
    }
    else
    {
      d4 = 0;
    }
  }
  return value;
}

//computes a more accurate value of the move (considers opponent's bitboard)
int val(const unsigned __int128 bitboardP, const unsigned __int128 bitboardO, size_t size)
{
  int PP = 0, PO = 0;
  for(size_t row = 0; row < size; row++)
  {
    for(size_t col = 0; col < size; col++)
    {
        PP += nb_series(bitboardP, row, col, size);
        PO += nb_series(bitboardO, row, col, size);
    }
  }
  return(PP - PO);
}


//computes the possible moves
struct p_moves possible_moves(size_t size, const unsigned __int128 bitboardW, const unsigned __int128 bitboardB)
{
  struct move_t l_moves[size*size];
  struct p_moves P_moves = {l_moves,0};
  struct move_t s_moves = {0,0};
  for (size_t row = 0; row < size; row++)
  {
    for (size_t col = 0; col < size; col++)
    {
      if(is_empty_cell(bitboardB, row, col, size) && is_empty_cell(bitboardW, row, col, size))
      {
        s_moves.row = row;
        s_moves.col = col;
        P_moves.l_moves[P_moves.n_of_moves] = s_moves;
        P_moves.n_of_moves ++;
      }
    }
  }
  return P_moves;
}

//returns the maximum value for minmax (beetween a move and the previous one)
struct node Max(struct node before, struct node after)
{
  if (after.value > before.value)
  {
    return after;
  }
  return before;
}

//returns the minimum value for minmax (beetween a move and the previous one)
struct node Min(struct node before, struct node after)
{
  if (after.value < before.value)
  {
    return after;
  }
  return before;
}

//evaluates a move (how worth it is to play in a particular cell)
struct node eval(unsigned __int128 bitboardP, unsigned __int128 bitboardO, struct node Node, size_t size)
{
  struct node Eval_node = Node;
  Eval_node.value = val(bitboardP, bitboardO, size);
  return Eval_node;
}

//checks if the game is over (if the bitboard is full)
char is_game_over(const struct p_moves P_moves)
{
  return(P_moves.n_of_moves == 0);
}

//the recursive part of the minmax algorithm. Separated from the minmax function to have less arguments to give
struct node minmax_rec(int depth, size_t size, unsigned __int128 bitboardP,
  unsigned __int128 bitboardO, char max_p, struct node best_node,struct node Node)
{
  struct p_moves P_moves = possible_moves(size,bitboardP,bitboardO);
  if((depth == 0) || (is_game_over(P_moves)))
  {
    if(max_p)
    {
      return eval(bitboardP, bitboardO, Node, size);
    }
    else
    {
      return eval(bitboardO, bitboardP, Node, size);
    }
  }
  if(max_p) //player turn
  {
    best_node.mv_node = P_moves.l_moves[0];
    best_node.value = -INFINITY;
    for (int i = 0; i < P_moves.n_of_moves; i++)
    {
      Node.mv_node = P_moves.l_moves[i];
      best_node = Max(best_node, minmax_rec(depth - 1, size, operation_on_token(bitboardP, P_moves.l_moves[i].row, P_moves.l_moves[i].col, size, '+'), bitboardO, 0, best_node, Node));
    }
  }
  else //opponent turn
  {
    best_node.mv_node = P_moves.l_moves[0];
    best_node.value = INFINITY;
    for (int i = 0; i < P_moves.n_of_moves; i++)
    {
      Node.mv_node = P_moves.l_moves[i];
      best_node = Min(best_node, minmax_rec(depth - 1,size, bitboardP, operation_on_token(bitboardO, P_moves.l_moves[i].row, P_moves.l_moves[i].col, size, '+'), 1, best_node, Node));
    }
  }
  return(best_node);
}

//The minmax function. returns the best move to play considering both bitboards of size "size" and planning "depth" steps ahead
struct move_t minmax(int depth, size_t size, const unsigned __int128 bitboardP, const unsigned __int128 bitboardO)
{
  unsigned __int128 bitboardPC = bitboardP;
  unsigned __int128 bitboardOC = bitboardO;
  struct node Node;
  struct node best_node;
  best_node = minmax_rec(depth,size,bitboardPC,bitboardOC,1,best_node,Node);
  return (best_node.mv_node);
}
