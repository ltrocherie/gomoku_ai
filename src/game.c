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

int place(struct board* bd, struct col_move col)
{
  if (!bd->m[col.m.row][col.m.col]) {
    bd->m[col.m.row][col.m.col] = col.c;
    return 0;
  }
  return -1;
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
