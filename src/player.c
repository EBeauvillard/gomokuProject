#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "bitboard.h"
#include "player.h"

#define DEFAULT_NB_PLAYERS 2
#define OPENING_SIZE 3

struct player
{
    char* name;
    enum color_t color;
    unsigned __int128 *bitboardB;
    unsigned __int128 *bitboardW;
    struct col_move_t* opening;
    size_t size;
};

static struct player p;

char const* get_player_name()  // gets the player name
{
    return (p.name);
}

struct col_move_t* propose_opening(size_t size)
{
    size_t middle = size/2;
    struct move_t mv0 = {middle-1,middle};
    struct move_t mv1 = {middle,middle};
    struct move_t mv2 = {middle+1,middle};

    p.opening = malloc(OPENING_SIZE * sizeof(struct col_move_t));
    p.opening[0].m = mv0;
    p.opening[0].c = BLACK;
    p.opening[1].m = mv1;
    p.opening[1].c = WHITE;
    p.opening[2].m = mv2;
    p.opening[2].c = BLACK;

    return p.opening;
}

int accept_opening(size_t size, const __attribute__((__unused__)) struct col_move_t* opening)
{
    if(size >= 5)
    {
        return 1;
    }
    return 0;
}

void initialize(size_t size, enum color_t id)
{
    srand(time(NULL));
    p.size = size;
    p.color = id;
    p.bitboardB = malloc(sizeof(unsigned __int128));
    *(p.bitboardB) = 0;
    p.bitboardW = malloc(sizeof(unsigned __int128));
    *(p.bitboardW) = 0;
    p.opening = NULL;
    p.name = "David";
}

struct move_t play(struct col_move_t const previous_moves[], size_t n_moves)
{
    if (n_moves >= OPENING_SIZE) {
        for (size_t i=1; i<=n_moves; i++) {
            if (i%DEFAULT_NB_PLAYERS == 0) {
                *(p.bitboardW) = operation_on_token(*(p.bitboardW), previous_moves[i-1].m.row, previous_moves[i-1].m.col, p.size, '+');
            } else {
                *(p.bitboardB) = operation_on_token(*(p.bitboardB), previous_moves[i-1].m.row, previous_moves[i-1].m.col, p.size, '+');
            }
        }
        n_moves -= OPENING_SIZE;
    }

    if(p.color == BLACK)
    {
        if(n_moves > 0)
        {
          //printf("move : {%zu,%zu}\n", previous_moves[n_moves-1].m.row, previous_moves[n_moves-1].m.col);
          *(p.bitboardW) = operation_on_token(*(p.bitboardW),previous_moves[n_moves-1].m.row,previous_moves[n_moves-1].m.col,p.size,'+');
        }
    }
    else
    {
        if(n_moves > 0)
        {
          //printf("move : {%zu,%zu}\n", previous_moves[n_moves-1].m.row, previous_moves[n_moves-1].m.col);
          *(p.bitboardB) = operation_on_token(*(p.bitboardB),previous_moves[n_moves-1].m.row,previous_moves[n_moves-1].m.col,p.size,'+');
        }
    }

    size_t col = (rand() % p.size);
    size_t row = (rand() % p.size);
    while((!(is_empty_cell(*(p.bitboardB),row,col,p.size))) || (!(is_empty_cell(*(p.bitboardW),row,col,p.size))))
    {
        //printf("in while : %lu %lu \n",row,col);
        col = (rand() % p.size);
        row = (rand() % p.size);
    }

    struct move_t move = {row,col};

    if(p.color == BLACK)
    {
        *(p.bitboardB) = operation_on_token(*(p.bitboardB),row,col,p.size,'+');
    }
    else
    {
        *(p.bitboardW) = operation_on_token(*(p.bitboardW),row,col,p.size,'+');
    }
    /*
    printf("random : \n");
    print_bits(*(p.bitboardB), p.size);
    printf("\n");
    print_bits(*(p.bitboardW), p.size);
    printf("\n");
    */
    return move;
}


void finalize()
{
    *(p.bitboardB) = 0;
    *(p.bitboardW) = 0;
    free(p.bitboardB);
    free(p.bitboardW);
    if (p.opening != NULL) {
      free(p.opening);
    }
}
