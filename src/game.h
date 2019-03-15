#include <stdio.h>
#include <stdlib.h>

struct board;

struct board ini_game(int n);

int place(struct board* bd, struct col_move col);
  
int is_winning(struct board bd);
