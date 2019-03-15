#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 11

struct board{
  char m[MAX_SIZE][MAX_SIZE];
  int size;
};

struct board ini_game(int n)
{
  struct board bd;
  bd.winner = 0;
  bd.size = n;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      bd.m[i][j] = 0;
    }
  }
  return bd;
}

int place(struct board* bd, struct col_move_t col)
{
  if (!bd->m[col.m.row][col.m.col]) {
    bd->m[col.m.row][col.m.col] = col.c;
    return 0;
  }
  return -1;
}

int align(struct board const bd, struct col_move_t col)
{
    int max = 0;
    for (size_t dir = 0; dir < 4; dir++) {
        ij = 0;
        if (dir == 0){
            size_t i;
            for (i = 0; i < bd.size && i > 0; i++) {
                struct move_t cas = {col.m[0]+i, col.m[1]};//la case qu'on est en train de regarder
                if (color(cas) != col.c) {//si le pion sur la case n'est pas de la couleur du joueur qui nous intéresse
                    i--;
                    break;
                }
            }
            size_t j;
            for (j = 0; j < bd.size && j > 0; j++) {
                struct move_t cas = {col.m[0]-j, col.m[1]};//la case qu'on est en train de regarder
                if (color(cas) != col.c) {//si le pion sur la case n'est pas de la couleur du joueur qui nous intéresse
                    j--;
                    break;
                }
            }
            ij = i+j;
        }
        if (dir == 1){
            size_t i;#TODO
        }


        if (ij > max){
            max = ij;
        }
        //vérifier que chaque case testée est entre 0 et bd.size pour chacune de ses coordonnées
    }
}

int is_winning(struct board bd)
{
  return bd.winner;
}

int main(int argc, char* argv)
{
  struct board bd = ini_game(5);
  place(&bd, 2, 3, 1);
  printf("%d\n",bd.m[2][3]);
}
