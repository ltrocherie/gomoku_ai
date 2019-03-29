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
  struct col_move_t moves[NB_PLAYERS+2];
  struct move_t m;
  struct col_move_t col_m;
  size_t n_moves = 0;
  int res = -1;
  if(swap_mode)
    activate_swap_mode(moves, &n_moves, board_size, players);
  else
    {
    (players[0].initialize)(board_size, WHITE);
    (players[1].initialize)(board_size, RED);
    }
  while(res == -1)
  {
    for(int i=0; i<NB_PLAYERS; i++)
  	{
	  m = (players[i].play)(moves,n_moves);
	  col_m.m = m;
	  col_m.c = players[i].color;
	  place(&board, col_m);
	  res = is_winning(board, col_m);
	  if(res != -1)
	    break;
	  enqueue(col_m,moves,&n_moves);
	}
  }
  if(res<=NB_PLAYERS)
    printf("Player %d is winner \n",res);
  //TODO function eliminate    
  //finalize(); TODO
  close_libs(players_libs);
  return 0;
}


