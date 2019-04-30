#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "bitboard.h"
#define UNUSED(X){ while(0){(void)X;}};

struct board ini_board(size_t n){
    struct board bd;
    bd.size = n;
    bd.b0 = 0;
    for (size_t i = 0; i < MAX_PLAYERS; i++) {
        bd.b[i] = 0;
    }
    //griser toutes les cases d'indice supérieur ou égal à n**2
        //car elles seront en-dehors du tableau
    for (size_t i = n*n; i < 128; i++) {
        bd.b0 |= 1<<(i);//tester avec i-1 en cas de bugs
    }
    return bd;
}

int place(struct board* bd, struct col_move_t cm){
  int n = bd->size;
  __int128 affix = (cm.m.row)*n + cm.m.col;
  for (size_t i = 0; i < MAX_PLAYERS; i++) {
    if (bd->b[i] & (1<<affix)){
            return -1;
        }
    }
    bd->b[cm.c] |= (1<<affix);
    return 0;
}

void board_display(const struct board* bd, size_t n){
  enum { base = 2, max_width = 128 };
  for(size_t i = 0; i < MAX_PLAYERS; i++){
    //printf("%d\n", bd->b[i]);
    __int128 n = bd->b[i] * bd->b[i];
    char a[max_width + 1] = { '\0' };
    char *p = a + max_width;
    for (; n != 0; n /= base) *--p = (char)('0' + n % base);

    printf("%s\n", p);
  }
  printf("Next\n");
  return;
}

int align(struct board const bd, struct col_move_t cm){
  int n = bd.size;
  printf("align : size = %d\n",n);
  printf("align : row = %ld, col = %ld\n", cm.m.row, cm.m.col);
  int max = 1;
  //int dir;
  int c;
  int i = cm.m.row, j = cm.m.col;
  printf("align : i = %d, j = %d\n",i, j);
  // int affix = (cm.m.row)*n + cm.m.col;
  assert(i>=0 && i<bd.size);
  assert(j>=0 && j<bd.size);
  printf("%d\n",cm.c);
  //direction verticale
  c = 1;
  UNUSED(c);
  UNUSED(n);
  /*
    for (int row = i-1; row >= 0; row--) {//on regarde au-dessus
    if (bd.b[cm.c] & (1<<(row*n+j))){
    c++;
    }else{
    break;
    }
    }
    for (int row = i+1; row < bd.size; row++) {//on regarde au-dessous
    if (bd.b[cm.c] & (1<<(row*n+j))){
    c++;
    }else{
    break;
    }
    }
    if (c > max){
    max = c;
    }

    //direction slash
    c = 1;
    for (int row = i-1, col = j+1; row >= 0 && col < bd.size; row--, col++) {
    if (bd.b[cm.c] & (1<<(row*n+col))){
    c++;
    }else{
    break;
    }
    }
    for (int row = i+1, col = j-1; row < bd.size && col >= 0; row++, col--) {
    if (bd.b[cm.c] & (1<<(row*n+col))){
    c++;
    }else{
    break;
    }
    }
    if (c > max){
    max = c;
    }

    //direction horizontale
    c = 1;
    for (ssize_t col = j+1; col < bd.size; col++) {//on regarde à droite
    if (bd.b[cm.c] & (1<<(i*n+col))){
    c++;
    }else{
    break;
    }
    }
    for (int col = j-1; col >= 0; col--) {//on regarde à gauche
    if (bd.b[cm.c] & (1<<(i*n+col))){
    c++;
    }else{
    break;
    }
    }
    if (c > max){
    max = c;
    }

    //direction antislash
    c = 1;
    for (ssize_t row = i+1, col = j+1; row < bd.size && col < bd.size; row++, col++) {
    if (bd.b[cm.c] & (1<<(row*n+col))){
    c++;
    }else{
    break;
    }
    }
    for (int row = i-1, col = j-1; row >= 0 && col >= 0; row--, col--) {
    if (bd.b[cm.c] & (1<<(row*n+col))){
    c++;
    }else{
    break;
    }
    }
    if (c > max){
    max = c;
    }
  */
  return max;
}
