#include <stdio.h>
#include <stdlib.h>
#include "gameAB.h"
#include "move.h"

//renvoie l'entier associé au gagnant s'il y en a un apres le move cm
//renvoie l'entier associé au perdant + 4 s'il y en a un après le move cm
//renvoie -1 s'il n'y a ni gagnant ni perdant
int is_winning(struct board bd, struct col_move_t cm)
{
  //printf("Is_winning : row = %lu, col = %lu\n", cm.m.row, cm.m.col);
  //printf("Is_winning : color = %d\n", cm.c);
  int res = align(bd,cm);
  //printf("Is_winning : res = %d\n", res);
  if (res >= 5)
    return cm.c;
  /*  if (align(bd, cm) > 5)
  return cm.c+4;*/
  return -1;
}
