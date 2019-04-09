#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "move.h"

//renvoie l'entier associé au gagnant s'il y en a un apres le move cm
//renvoie l'entier associé au perdant + 4 s'il y en a un après le move cm
//renvoie -1 s'il n'y a ni gagnant ni perdant
int is_winning(struct board bd, struct col_move_t cm)
{
  if (align(bd, cm) >= 5)
    return cm.c;
  /*  if (align(bd, cm) > 5)
  return cm.c+4;*/
  return -1;
}
