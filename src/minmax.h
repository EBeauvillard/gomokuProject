#ifndef MINMAX_H
#define MINMAX_H

//The minmax function. returns the best move to play considering both bitboards of size "size" and planning "depth" steps ahead
struct move_t minmax(int depth, size_t size, const unsigned __int128 bitboardP, const unsigned __int128 bitboardO);

#endif
