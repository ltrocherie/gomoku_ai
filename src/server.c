#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>
#include "game.h"

struct player{
  char * name;
  enum color_t color;
  struct col_move_t const previous_moves[];
  size_t n_moves;
  char const* (*get_player_name)();
  struct col_move_t* (*propose_opening)(size_t size);
  int (*accept_opening)(size_t size, const struct col_move_t* opening);
  void (*initialize)(size_t size, enum color_t id);
  struct move_t (*play)(struct col_move_t const previous_moves[], size_t n_moves);
  void (*finalize)();
};

int main(int argc, char* argv[])
{
  struct col_move_t moves;
  void* players_libs[MAX_PLAYERS];
  size_t board_size = 0;
  int swap_mode = 0;
  parse_arg(argc, argv,&board_size, &swap_mode, players_libs);
  if(error_management(&board_size,players_libs))
    exit(1);
  struct player players[MAX_PLAYERS];
  struct player first_player = players[0];
  struct player second_player = players[1];
  initialise_players_data(players, players_libs);
  if(swap_mode)
    activate_swap_mod(&moves,board_size, first_player, second_player);
  //TODO boucle de jeu   
  close_libs(players_libs);
  return 0;
}
