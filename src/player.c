#include<stdio.h>
#include<stdlib.h>

#include "player.h"

#define MAX_NAME_LENGTH 10
#define NB_OPENING_MOVE 3

/*
  These functions are public. The description of the functions
  is in player.h
 */
//char* names[2] = {"random1", "random2"};

int belongs(struct col_move_t const tab[], struct move_t mv, size_t n);

//fonction publique
char const *get_player_name(){
  char *name;
  name = "random";
  return name;
}

//fonction publique
struct col_move_t* propose_opening(size_t size){
  struct col_move_t *move = malloc(100 * sizeof(struct col_move_t));
  for(int i = 0; i<NB_OPENING_MOVE; i++){
    struct move_t mv;
    mv.row = rand()%size;
    mv.col = rand()%size;
    struct col_move_t mv_next;
    mv_next.m = mv;
    mv_next.c = i%2;
    if(!belongs(move, mv, i))
      move[i] = mv_next;
    else
      i--;
  }
  return move;
}

//fonction publique
int accept_opening(size_t size, const struct col_move_t* opening){
  return 1;
}

//fonction publique
void initialize(size_t size, enum color_t id){
  BOARD_SIZE = size;
  PLAYER_COLOR = id;
  srand(42);
  all_moves = malloc(sizeof(int)*BOARD_SIZE*BOARD_SIZE);
  all_moves_size = 0;
  return;
}

int belongs(struct col_move_t const tab[], struct move_t mv, size_t n){
  if(n != 0)
    {
      for(size_t i=0; i < n; i++){
	    if(mv.row == tab[i].m.row && mv.col == tab[i].m.col)
	  return 1;
      }
    }
  return 0;
}

//fonction publique
struct move_t play(struct col_move_t const previous_moves[],
		   size_t n_moves){
  for (size_t i = 0; i < n_moves; i++) {
      all_moves[all_moves_size] = previous_moves[i];
      all_moves_size++;
  }
  struct move_t next_move = {.row = rand()%BOARD_SIZE, .col = rand()%BOARD_SIZE};
  while(belongs(all_moves, next_move, n_moves)){
    next_move.row = rand()%BOARD_SIZE;
    next_move.col = rand()%BOARD_SIZE;
  }
  return next_move;
}

//fonction publique
void finalize(){
  return;
}
