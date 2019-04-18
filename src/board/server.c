#include <stdio.h>
#include <stdlib.h>
#include "server_functions.h"

int main(int argc, char* argv[])
{

  void* players_libs[NB_PLAYERS];
  size_t board_size;
  int swap_mode = 0;
  parse_arg(argc, argv,&board_size, &swap_mode, players_libs);
  if(error_management(board_size,players_libs))
    {
      exit(1);
    }
  struct player players[NB_PLAYERS];
  initialize_players_data(players, players_libs);
  struct board board = ini_board(board_size);
  struct col_move_t* moves = NULL;
  size_t n_moves = 0;
  int res = -1;
  if(swap_mode)
    moves = activate_swap_mode(&n_moves, board_size, players);
  else
    {
      moves = malloc(100 * sizeof(struct col_move_t));
      (players[0].initialize)(board_size, WHITE);
      (players[1].initialize)(board_size, RED);
    }

  while(res == -1 &&  n_moves != board_size*board_size)
    play_run(moves, &n_moves, players, &board, board_size, &res);

  if( n_moves == board_size*board_size)
    printf("No player has aligned fives same colors\n");
  else if(res<=NB_PLAYERS)
    printf("Player %d is winner \n",res);
  //TODO function eliminate
  //finalize(); TODO
  players[0].finalize();
  players[1].finalize();
  close_libs(players_libs);
  free(moves);
  return 0;
}