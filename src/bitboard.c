#include <stdio.h>
#include <stdint.h>
#include "bitboard.h"

//Returns True if the cell targeted is empty, else returns false
char is_empty_cell(unsigned __int128 bitboard, size_t line, size_t column, size_t size) {
  if ((line >= size) || (column >= size)) {
    printf("error\n");
    return 0;
  }
  size_t ind_cell = size * line + column + 1;
  return !( (bitboard >> (ind_cell - 1) ) & 1);
}

//Add a token on the targeted cell
unsigned __int128 operation_on_token(unsigned __int128 bitboard, size_t line, size_t column, size_t size, int operator) {
  size_t ind_cell = size * line + column;
  unsigned __int128 tmp = bitboard;
  switch (operator) {
  case '+':
    bitboard = bitboard | (((tmp >> ind_cell) | 1) << ind_cell);
    break;
  default:
    break;
  }
  return bitboard;
}

//Display on terminal the bitboard taken in argument
void print_bits(unsigned __int128 bitboard, size_t size)
{
  unsigned int bit = 0;
  unsigned int nb_cells = size * size;
  while (bit < (sizeof(unsigned __int128) * 8) && bit < nb_cells)
  {
    printf("%i ", bitboard & 0x01);
    bitboard = bitboard >> 1;
    bit++;
    if(!(bit % size)) // == 0
      printf("\n");
  }
}

int serie_win(unsigned __int128 const * const bitboard, size_t const size){
  int cpt_l = 0;
  int cpt_c = 0;
  // Verifying a winning serie (line or column)
  for(unsigned int line = 0; line < size; line++){
    for(unsigned int column = 0; column < size; column++){
      // Line
      if(!is_empty_cell(*bitboard, line, column, size))
        cpt_l++;
      else{
        if(cpt_l >= NB_SERIE)
          return SUCCESS;
        cpt_l = 0;
      }
      // Column
      if(!is_empty_cell(*bitboard, column, line, size))
        cpt_c++;
      else{
        if(cpt_c >= NB_SERIE)
          return SUCCESS;
        cpt_c = 0;
      }
    }
    if(cpt_l >= NB_SERIE || cpt_c >= NB_SERIE)
      return SUCCESS;
    cpt_l = 0;
    cpt_c = 0;
  }
  return FAILURE;
}

int diag_t2b_win(unsigned __int128 const * const bitboard, size_t const size){
  int cpt_diag_t2b_top = 0;
  int cpt_diag_t2b_bot = 0;
  //Veryfying a diagonal winning serie (top to bot)
  for(unsigned int i = 0; i < size; i++){
    unsigned int lin = i;
    unsigned int col = 0;
    while(col < size &&
          lin < size){

      // Upper right corner
      if(!is_empty_cell(*bitboard, lin, col, size)){
        cpt_diag_t2b_top++;
      } else {
        if(cpt_diag_t2b_top >= NB_SERIE)
          return SUCCESS;
        cpt_diag_t2b_top = 0;
      }

      // Lower left corner
      if(!is_empty_cell(*bitboard, col, lin, size)){
        cpt_diag_t2b_bot++;
      } else {
        if(cpt_diag_t2b_bot >= NB_SERIE)
          return SUCCESS;
        cpt_diag_t2b_bot = 0;
      }

      col++;
      lin++;
    }
    if(cpt_diag_t2b_top >= NB_SERIE || cpt_diag_t2b_bot >= NB_SERIE)
      return SUCCESS;
    cpt_diag_t2b_top = 0;
    cpt_diag_t2b_bot = 0;
  }
  return FAILURE;
}


int diag_b2t_win(unsigned __int128 const * const bitboard, size_t const size){
  int cpt_diag_b2t_top = 0;
  int cpt_diag_b2t_bot = 0;

  //Veryfying a diagonal winning serie (bot to top)
  //Upper left corner
  for(unsigned int i = 0; i < size; i++){
    unsigned int lin = 0;
    int col = size - 1 - i;
    while((col >= 0) && (lin < size)){
      if(!is_empty_cell(*bitboard, lin, col, size)){
        cpt_diag_b2t_top++;
      } else {
        if(cpt_diag_b2t_top >= NB_SERIE)
          return SUCCESS;
        cpt_diag_b2t_top = 0;
      }
      col--;
      lin++;
    }
    if(cpt_diag_b2t_top >= NB_SERIE)
      return SUCCESS;
    cpt_diag_b2t_top = 0;
  }

  //Lower right corner
  for(unsigned int i = 1; i < size; i++){
    unsigned int lin = i;
    int col = size - 1;
    while(col >= 0 &&
          lin < size){
      if(!is_empty_cell(*bitboard, lin, col, size)){
        cpt_diag_b2t_bot++;
      } else {
        if(cpt_diag_b2t_bot >= NB_SERIE)
          return SUCCESS;
        cpt_diag_b2t_bot = 0;
      }
      col--;
      lin++;
    }
    if(cpt_diag_b2t_bot >= NB_SERIE)
      return SUCCESS;
    cpt_diag_b2t_bot = 0;
  }

  return FAILURE;
}

char is_won(unsigned __int128 bitboard, size_t size){
  return (serie_win(&bitboard, size))
    || (diag_t2b_win(&bitboard, size))
    || (diag_b2t_win(&bitboard, size));
}
