#include <stdio.h>
#include <stdlib.h>

#include "move.h"
#include "game_bit.h"

void enqueue(struct col_move_t m, struct col_move_t moves[], size_t* n_moves)
{
  if(*n_moves != NB_PLAYERS && *n_moves != 2*NB_PLAYERS)
  {
    moves[*n_moves] = m;
    *n_moves += 1;
  }else{
    for(int i=0; i<NB_PLAYERS-1;i++)
	{
	  moves[i] = moves[*n_moves-NB_PLAYERS+1+i];
	  moves[NB_PLAYERS-1] = m;
	  *n_moves = NB_PLAYERS;
	}
  }
}

// void enqueue(struct col_move_t m, struct col_move_t* moves, size_t* n_moves)
// {
//   if(*n_moves%100 == 0 && *n_moves != 0)
//     moves = realloc(moves, (*n_moves+100)*sizeof(struct col_move_t));
//   *(moves + *n_moves) = m;
//   *n_moves = *n_moves+1;
// }
