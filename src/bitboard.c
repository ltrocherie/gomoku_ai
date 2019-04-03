#include <stdio.h>
#include <stdlib.h>

#include "move.h"
#include "bitboard.h"

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
        bd.b0 &= 1<<(i);//tester avec i-1 en cas de bugs
    }
    return bd;
}

int place(struct board* bd, struct col_move_t cm){
  int n = bd->size;
  int affix = (cm.m.row)*n + cm.m.col;
  for (size_t i = 0; i < MAX_PLAYERS; i++) {
    if (bd->b[i] & (1<<affix)){
            return -1;
        }
    }
    bd->b[cm.c] &= (1<<affix);
    return 0;
}

int align(struct board const bd, struct col_move_t cm){
  int n = bd.size;
    int max = 1;
    //int dir;
    int c;
    size_t i = cm.m.row, j = cm.m.col;
    // int affix = (cm.m.row)*n + cm.m.col;

    //direction verticale
    c = 1;
    for (size_t row = i-1; row >= 0; row--) {//on regarde au-dessus
        if (bd.b[cm.c] & (1<<(row*n+j))){
            c++;
        }else{
            break;
        }
    }
    for (size_t row = i+1; row < bd.size; row++) {//on regarde au-dessous
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
    for (size_t row = i-1, col = j+1; row >= 0 && col < bd.size; row--, col++) {
        if (bd.b[cm.c] & (1<<(row*n+col))){
            c++;
        }else{
            break;
        }
    }
    for (size_t row = i+1, col = j-1; row < bd.size && col >= 0; row++, col--) {
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
    for (size_t col = j+1; col < bd.size; col++) {//on regarde à droite
        if (bd.b[cm.c] & (1<<(i*n+col))){
            c++;
        }else{
            break;
        }
    }
    for (size_t col = j-1; col >= 0; col--) {//on regarde à gauche
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
    for (size_t row = i+1, col = j+1; row < bd.size && col < bd.size; row++, col++) {
        if (bd.b[cm.c] & (1<<(row*n+col))){
            c++;
        }else{
            break;
        }
    }
    for (size_t row = i-1, col = j-1; row >= 0 && col >= 0; row--, col--) {
        if (bd.b[cm.c] & (1<<(row*n+col))){
            c++;
        }else{
            break;
        }
    }
    if (c > max){
        max = c;
    }

    return max;
}
