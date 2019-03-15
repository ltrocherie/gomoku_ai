#include<stdio.h>
#include<stdlib.h>

#include "player.h"

#define MAX_NAME_LENGTH 10
#define NB_OPENING_MOVE 3

char const* get_player_name(){
  char* name = malloc(MAX_NAME_LENGTH*sizeof(char));
  scanf("[a-zA-Z0-9 -_]%s", name);
  return name;
};

struct col_move_t* propose_opening(size_t size){
  struct col_move_t* move = malloc(NB_OPENING_MOVE * sizeof(struct col_move_t));
  for(int i = 0; i<NB_OPENING_MOVE; i++){
    struct move_t mv;
    mv.row = i;
    mv.col = i;
    struct col_move_t mv_next;
    mv_next.m = mv;
    mv_next.c = i%2;
    move[i] = mv_next;
  }
  return move;
};
