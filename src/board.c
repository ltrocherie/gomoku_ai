#include <stdlib.h>
#include <stdio.h>
#include "board.h"

#define MAX_SIZE 11

struct board{
  char m[MAX_SIZE][MAX_SIZE];
  size_t size;
};

//initialise un board
struct board ini_game(int n)
{
  struct board bd;
  bd.size = n;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      bd.m[i][j] = 0;
    }
  }
  return bd;
}

//place un pion sur bd (infos dans cm)
int place(struct board* bd, struct col_move_t cm)
{
  if (!bd->m[cm.m.row][cm.m.col]) {
    bd->m[cm.m.row][cm.m.col] = cm.c;
    return 0;
  }
  return -1;
}

//retourne le nombre de pions maximal de la couleur cm.c alignés avec celui en
//position cm.m sur bd
int align(struct board const bd, struct col_move_t cm)
{
  int max = 1;
  size_t i = cm.m.row, j = cm.m.col;
  for (size_t dir=0;dir<4;dir++){

    if (dir == 0){ //on travaille sur l'axe vertical
      int c = 1;
      for (size_t row=i-1;row>0;row--){ //on compte le nombre de pions similaires
	if (bd.m[row][j] == cm.c) //au dessus
	  c++;
	else
	  break;
      }
      for (size_t row=i+1;row<bd.size;row++){ //on compte le nombre de pions
	if (bd.m[row][j] == cm.c)         //similaires en dessous
	  c++;
	else
	  break;
      }
      if (c > max)
	max = c;
    }
    if (dir == 1){ //on travaille sur l'axe SO-NE
      int c = 1;
      for (size_t row=i-1,col=j+1;row>0,col<bd.size;row--,col++){ //on compte
	if (bd.m[row][col] == cm.c) //le nombre de pions similaires au dessus
	  c++;                      //à droite
	else
	  break;
      }
      for (size_t row=i+1,col=j-1;col>0,row<bd.size;col--,row++){ //on compte le
	if (bd.m[row][col] == cm.c) //nombre de pions similaires en dessous à
	  c++;                      //gauche
	else
	  break;
      }
      if (c > max)
	max = c;
    }
    if (dir == 2){ //on travaille sur l'axe horizontal
      int c = 1;
      for (size_t col=j+1;col<bd.size;col++){ //on compte le nombre de pions
	if (bd.m[i][col] == cm.c) //similaires à droite
	  c++;
	else
	  break;
      }
      for (size_t col=j-1;col>0;col--){ //on compte le nombre de pions
	if (bd.m[i][col] == cm.c)         //similaires à gauche
	  c++;
	else
	  break;
      }
      if (c > max)
	max = c;
    }

    if (dir == 3){ //on travaille sur l'axe NO-SE
      int c = 1;
      for (size_t row=i+1,col=j+1;col<bd.size,row<bd.size;row++,col++){ //on
    	if (bd.m[row][col] == cm.c) //compte le nombre de pions similaires en
          c++;                      //dessous à droite
    	else
    	  break;
      }
      for (size_t row=i-1,col=j-1;col>0,row>0;col--,row--){ //on compte le
    	if (bd.m[row][col] == cm.c) //nombre de pions similaires en dessous à
    	  c++;                      //gauche
    	else
    	  break;
      }
      if (c > max)
	max = c;
    }
  }
  return max;
}
