#include <stdio.h>
#include <stdlib.h>

struct board{
  char m[11][11];
  int size;
  int winner;
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

void place(struct board* bd, int l, int c, int pl)
{
  if (!bd->m[l][c]) {
    bd->m[l][c] = pl; }
  else {
    bd->winner = pl%2 + 1;
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
