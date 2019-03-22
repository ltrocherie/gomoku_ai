#include<stdio.h>
#include<stdlib.h>

#include "../src/player.h"

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

int main(){
  test_get_player_name();
  test_propose_opening();
  return 0;
}
