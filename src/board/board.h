#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <stdio.h>
#include "../server_dir/move.h"

#define MAX_PLAYERS 4
#define MAX_SIZE 11

struct board{
  char m[MAX_SIZE][MAX_SIZE];
  size_t size;
};

//initialise un board de taille n
struct board ini_board(size_t n);

//place un pion sur bd (infos dans cm)
int place(struct board* bd, struct col_move_t cm);

//retourne le nombre de pions maximal de la couleur cm.c alignés avec celui en
//position cm.m sur bd
int align(struct board const bd, struct col_move_t cm);

//affiche le board sur la sortie standard
void board_display(const struct board* bd, size_t n);

#endif
