#ifndef BITBOARD_H
#define BITBOARD_H

#include <stddef.h>

#define NB_SERIE 5
#define FAILURE 0
#define SUCCESS 1

/* This function checks if there is a token the cell at the intersection line-column. size is the size of the bitboard (size*size) > 0.
   Note : line-columns indexes starts at 0. line = 0 and column = 0 is the first cell of the bitboard.
   Returns 1 if the cell is empty, 0 otherwise.
*/
char is_empty_cell(unsigned __int128 bitboard, size_t line, size_t column, size_t size);

/*
  this function prints a bitboard size*size with size > 0.
*/
void print_bits(unsigned __int128 bitboard, size_t size);

/*
  PRECOND: Targeted cell is empty
*/
unsigned __int128 operation_on_token(unsigned __int128 bitboard, size_t line, size_t column, size_t size, int operator);

/*
  this function tests if a player (with a bitboard) won the game
*/
char is_won(unsigned __int128 bitboard, size_t size);


#endif
