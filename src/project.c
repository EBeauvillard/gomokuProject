#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "move.h"
#include "tools.h"
#include "bitboard.h"

enum MODES { SWAP, STANDARD };

static int SIZE = DEFAULT_SIZE;
static enum MODES MODE = STANDARD;
static int NB_PLAYERS = DEFAULT_NB_PLAYERS;
static char* PLAYER1;
static char* PLAYER2;


/* Function for parsing the options of the program
 * -n N : initialize the board size with N
 * -o : initialize the mode to SWAP
 */
void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "on:")) != -1) {
    int size;
    switch (opt) {
    case 'o':
      MODE = SWAP;
      break;
    case 'n':
      size = *optarg - '0';
      if (size >= MIN_SIZE && size <= MAX_SIZE) {
        SIZE = size;
      } else {
        fprintf(stderr, "Invalid board size. You should choose a size between %d and %d included.\n", MIN_SIZE, MAX_SIZE);
        exit(EXIT_FAILURE);
      }
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: ./install/server -n [N] -o ./install/player1.so ./install/player2.so\n");
      exit(EXIT_FAILURE);
    }
  }

  if (argc - optind < 2) {
    fprintf(stderr, "Usage: ./install/server -n [N] -o ./install/player1.so ./install/player2.so\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0; (optind < argc) && (i <= 1); optind++) {
    if (i==0) {
      PLAYER1 = argv[optind];
    } else {
      PLAYER2 = argv[optind];
    }
    i++;
  }
  printf("Players : %s %s\n\n", PLAYER1, PLAYER2);
}


/********************************/
/*  COMMUNICATION WITH PLAYERS  */
/********************************/

// Function to get the opening of a player
struct col_move_t* get_opening_player(void* handle, size_t size) {
  struct col_move_t* (*propose_opening)(size_t);
  char* error;

  propose_opening = dlsym(handle, "propose_opening");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }

  struct col_move_t* moves = (*propose_opening)(size);
  return moves;
}

// Function to know if the player accepts an opening or not
int get_accepting_player(void* handle, size_t size, struct col_move_t* opening) {
  int (*accept_opening)(size_t, const struct col_move_t*);
  char* error;

  accept_opening = dlsym(handle, "accept_opening");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }

  int accepted = (*accept_opening)(size, opening);
  return accepted;
}

// Function to get a move frome a player
struct move_t get_move_player(void* handle, struct col_move_t const previous_moves[], size_t n_moves) {
  struct move_t (*play)(struct col_move_t const [], size_t);
  char* error;

  play = dlsym(handle, "play");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }

  struct move_t move = (*play)(previous_moves, n_moves);
  return move;
}

// Function to initialize a player
void initialize_player(void* handle, size_t size, enum color_t id) {
  void (*initialize)(size_t, enum color_t);
  char* error;

  initialize = dlsym(handle, "initialize");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }

  (*initialize)(size, id);
}

// Function to finalize a player
void finalize_player(void* handle) {
  void (*finalize)();
  char* error;

  finalize = dlsym(handle, "finalize");
  if ((error = dlerror()) != NULL)  {
    fputs(error, stderr);
    exit(1);
  }

  (*finalize)();
}

////////////////////////////////////////////////////////////////
int main(int argc,  char* argv[]) {
  parse_opts(argc, argv);

  /***********************/
  /*  PLAYERS' HANDLERS  */
  /***********************/
  void* handle_player1;
  void* handle_player2;

  handle_player1 = dlopen (PLAYER1, RTLD_LAZY);
  if (!handle_player1) {
    fputs (dlerror(), stderr);
    exit(1);
  }

  handle_player2 = dlopen (PLAYER2, RTLD_LAZY);
  if (!handle_player2) {
    fputs (dlerror(), stderr);
    exit(1);
  }

  unsigned __int128 *bitboardB = malloc(sizeof(unsigned __int128));
  unsigned __int128 *bitboardW = malloc(sizeof(unsigned __int128));
  *(bitboardB) = 0;
  *(bitboardW) = 0;


  /***********************/
  /*      GAME LOOP      */
  /***********************/
  int current_player = NB_PLAYERS - 1;
  void* players[] = { handle_player1, handle_player2 };
  struct col_move_t* moves;
  int nb_moves = 0;
  int size_moves = 4;
  moves = malloc(size_moves * sizeof(*moves));

  if (MODE == SWAP) {
    struct col_move_t* tmp = get_opening_player(handle_player1, SIZE);
    for (int i=1; i<=OPENING_SIZE; i++) {
      struct col_move_t m = { tmp[i-1].m, tmp[i-1].c };

      add_move(&m, moves, &size_moves, &nb_moves);

      if (i%DEFAULT_NB_PLAYERS == 0) {
        *bitboardW = operation_on_token(*bitboardW, m.m.row, m.m.col, SIZE, '+');
      } else {
        *bitboardB = operation_on_token(*bitboardB, m.m.row, m.m.col, SIZE, '+');
      }
    }
    int opening_accepted = get_accepting_player(handle_player1, SIZE, moves);

    if (opening_accepted) {
      initialize_player(handle_player1, SIZE, BLACK);
      initialize_player(handle_player2, SIZE, WHITE);
    } else {
      initialize_player(handle_player1, SIZE, WHITE);
      initialize_player(handle_player2, SIZE, BLACK);
    }
  } else {
    initialize_player(handle_player1, SIZE, BLACK);
    initialize_player(handle_player2, SIZE, WHITE);
  }

  for (int i=0; i<SIZE*SIZE; i++) {
    void* p = next_player(&current_player, players, NB_PLAYERS);
    struct move_t m;

    /* Giving to the player a list of previous moves starting from the last move issued by the player if it exists,
    otherwise from the beginning of the game */
    if ((nb_moves < NB_PLAYERS) || ((MODE == SWAP) && (nb_moves <= OPENING_SIZE + NB_PLAYERS))) {
      m = get_move_player(p, moves, nb_moves);
    } else {
      m = get_move_player(p, &moves[nb_moves-NB_PLAYERS], NB_PLAYERS);
    }

    struct col_move_t move = { m, (enum color_t) current_player };

    int col = m.col;
    int row = m.row;

    // Updating servers' bitboards with the move played
    switch ((enum color_t) current_player) {
      case BLACK:
        *bitboardB = operation_on_token(*bitboardB, row, col, SIZE, '+');
        break;
      case WHITE:
        *bitboardW = operation_on_token(*bitboardW, row, col, SIZE, '+');
        break;
      default:
        break;
    }

    if (is_won(*(bitboardW), SIZE) || is_won(*(bitboardB), SIZE)) {
      printf("*** Player %d won ! ***\n\n", current_player + 1);
      break;
    }
    if (nb_moves <= SIZE * SIZE) {
      moves = add_move(&move, moves, &size_moves, &nb_moves);
    }
  }

  for (int i=0; i < NB_PLAYERS; i++) {
    finalize_player(players[i]);
    dlclose(players[i]);
  }
  printf("Bitboard P1 : \n");
  print_bits(*bitboardB, SIZE);
  printf("Bitboard P2 : \n");
  print_bits(*bitboardW, SIZE);
  free(moves);
  free(bitboardB);
  free(bitboardW);
  return EXIT_SUCCESS;
}
