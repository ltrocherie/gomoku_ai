#ifndef GAME_H
#define GAME_H

//#include "player.h"
#ifdef B
#include "../bitboard/bitboard.h"
#else
#include "../board/board.h"
#endif

#define NB_PLAYERS 2
//renvoie l'entier associé au gagnant s'il y en a un apres le move cm
//renvoie l'entier associé au perdant + 4 s'il y en a un après le move cm
//renvoie -1 s'il n'y a ni gagnant ni perdant
int is_winning(struct board bd, struct col_move_t cm);
//int test_valid(struct board bd, struct col_move_t cm, enum color color);
#endif
