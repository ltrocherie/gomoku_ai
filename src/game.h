#ifndef GAME_H
#define GAME_H

#include "move.h"
#include "player.h"

struct board;

struct board ini_game(int n);

int place(struct board* bd, struct col_move_t col);
  
int is_winning(struct board bd);

void parse_arg(int argc, char* argv[], void* players_libs[]);

int error_management(void* players_libs[]);

void initialise_players_data(struct player players[], void* players_libs[]);

void close_libs(void* players_libs[]);

#endif
