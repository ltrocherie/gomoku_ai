#ifndef _SERVER_FUNCTIONS_H_
#define _SERVER_FUNCTIONS_H_

#include "game.h"

#define _GNU_SOURCE

struct player{
  char const* name;
  enum color_t color;
  size_t n_moves;
  char const* (*get_player_name)(void);
  struct col_move_t* (*propose_opening)(size_t size);
  int (*accept_opening)(size_t size, const struct col_move_t* opening);
  void (*initialize)(size_t size, enum color_t id);
  struct move_t (*play)(struct col_move_t const previous_moves[], size_t n_moves);
  void (*finalize)();
};

void parse_arg(int argc, char* argv[], size_t* board_size, int* swap_mode, void* players_libs[]);

int error_management(size_t board_size, void* players_libs[]);

void initialize_players_data(struct player* players, void* players_libs[]);

struct col_move_t* activate_swap_mode(size_t* n_moves, size_t board_size, struct player players[]);

void play_run(struct col_move_t* moves, size_t* n_moves, struct player players[], struct board* board, size_t board_size, int* res);

void close_libs(void* players_libs[]);

#endif
