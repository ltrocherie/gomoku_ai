#include<stdio.h>
#include<stdlib.h>

#include "../src/player_random/player.h"
/*
extern size_t BOARD_SIZE;
extern size_t PLAYER_COLOR;
*/
int test_get_player_name(){
  printf("Le nom du joueur est %s\n", get_player_name());
  return 0;
}

int test_propose_opening(){
  struct col_move_t *mov = propose_opening(6);
  for(size_t i = 0; i < 3; i++){
    printf("Coup : %ld\n", i);
    printf("Couleur : %d\n", mov[i].c);
    printf("Colonne : %ld\n", mov[i].m.col);
    printf("Ligne : %ld\n", mov[i].m.row);
  }
  return 0;
}

int test_initialize(){
  int size = 10;
  initialize(size, 0);
  printf("Taille du board : %ld\n", BOARD_SIZE);
  printf("Couleur du joueur : %d\n", PLAYER_COLOR);
  return 0;
}
/*
int test_play(){
  struct col_move_t m ={{1,3},0};
  struct col_move_t tab[1] = {m};
  struct move_t mov = play(tab, 1);
  return 0;
}
*/

int main(){
  test_get_player_name();
  test_propose_opening();
  test_initialize();
  return 0;
}
