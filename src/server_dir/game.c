#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "move.h"

//renvoie l'entier associé au gagnant s'il y en a un apres le move cm
//renvoie l'entier associé au perdant + 4 s'il y en a un après le move cm
//renvoie -1 s'il n'y a ni gagnant ni perdant
int is_winning(struct board bd, struct col_move_t cm)
{
  int res = align(bd,cm);
  if (res >= 5)
    return cm.c;
  return -1;
}

/*
int test_valid(struct board bd, struct col_move_t cm, enum color color)
{
  return( bd[cm.m.row, cm.m.col]== -1 &&
	 cm.m.col > 0 && cm.m.col < bd.size &&
	 cm.m.row > 0 && cm.m.row < bd.size &&
	  cm.c == color)
}
*/
