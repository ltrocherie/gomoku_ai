#include <stdlib.h>
#include <stdio.h>
#include "game.h"

int main(int argc, char* argv[])
{
  struct board bd = ini_game(5);
  struct col_move_t moves[9];
  moves[0] = {.m = {.row = 2, .col = 2}, .c = 0}
  moves[1] = {.m = {.row = 2, .col = 3}, .c = 1}
  moves[2] = {.m = {.row = 3, .col = 1}, .c = 0}
  moves[3] = {.m = {.row = 3, .col = 3}, .c = 1}
  moves[4] = {.m = {.row = 1, .col = 3}, .c = 0}
  moves[5] = {.m = {.row = 1, .col = 5}, .c = 1}
  moves[6] = {.m = {.row = 0, .col = 5}, .c = 0}
  moves[7] = {.m = {.row = 4, .col = 2}, .c = 1}
  moves[8] = {.m = {.row = 4, .col = 0}, .c = 0}

  for (int i=0;i<9;i++)
    place(&bd, moves[i]);  

  if (is_winning(bd, moves[7]) == -1){
    printf("Premier test échoué\n");
    return EXIT_FAILURE;}
  printf("Premier test réussi");

  if (is_winning(bd, moves[8]) == 0){
    printf("Second test échoué\n");
    return EXIT_FAILURE;}
  printf("Second test réussi");

  return EXIT_SUCCESS;
}
