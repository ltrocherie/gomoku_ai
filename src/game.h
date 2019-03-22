#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "player.h"

#define MAX_PLAYERS 2

struct board;

struct board ini_game(int n);

int place(struct board* bd, struct col_move_t col);

int align(struct board const bd, struct col_move_t col)
  
int is_winning(struct board bd);

void parse_arg(int argc, char* argv[], size_t* board_size, int* swap_mode, void* players_libs[]);

int error_management(size_t board_size, void* players_libs[]);

void initialise_players_data(struct player players[], void* players_libs[]);

void activate_swap_mode(struct col_move_t* moves, size_t board_size, struct player* first_player, struct player* first_player);

void close_libs(void* players_libs[]);

#endif
