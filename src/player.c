#include<stdio.h>
#include<stdlib.h>

#include "player.h"

#define MAX_NAME_LENGTH 10
#define NB_OPENING_MOVE 3

int belongs(struct col_move_t const tab[], struct move_t mv, size_t n);

/*
  These functions are public. The description of the functions
  is in player.h
 */

static size_t BOARD_SIZE;
static int PLAYER_COLOR;

char const *get_player_name(){
  char *name = malloc(MAX_NAME_LENGTH*sizeof(char));
  name = "random";
  return name;
}

struct col_move_t* propose_opening(size_t size){
  struct col_move_t *move = malloc(NB_OPENING_MOVE * sizeof(struct col_move_t));
  for(int i = 0; i<NB_OPENING_MOVE; i++){
    struct move_t mv;
    mv.row = rand()%size;
    mv.col = rand()%size;
    struct col_move_t mv_next;
    mv_next.m = mv;
    mv_next.c = i%2;
    move[i] = mv_next;
  }
  return move;
}

int accept_opening(size_t size, const struct col_move_t* opening){
  return 1;
}


void initialize(size_t size, enum color_t id){
  BOARD_SIZE = size;
  PLAYER_COLOR = id;
  srand(42);
  return;
}

int belongs(struct col_move_t const tab[], struct move_t mv, size_t n){
  for(size_t i; i < n; i++){
    if(mv.row == tab[i].m.row && mv.col == tab[i].m.col)
      return 1;
  }
  return 0;
}

struct move_t play(struct col_move_t const previous_moves[],
		   size_t n_moves){
  struct move_t next_move;
  while(!belongs(previous_moves, next_move, n_moves)){
    next_move.row = rand()%BOARD_SIZE;
    next_move.col = rand()%BOARD_SIZE;
  }
  return next_move;
}

void finalize(){
  return;
}

