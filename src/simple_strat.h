#ifndef SIMPLE_STRAT_H
#define SIMPLE_STRAT_H
#include <stdio.h>

//Plays by putting each token besides each other (if the cell is not full)
struct move_t simple_strat(unsigned __int128 bitboardP, unsigned __int128 bitboardO, size_t size);

#endif
