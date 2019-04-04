#ifndef BITBOARD_H
#define BITBOARD_H

#define MAX_PLAYERS 4

struct board{
    __int128 b0;//les positions jouables sont marquées avec des 0
    __int128 b[MAX_PLAYERS];//les positions où le joueur a des pions sont marquées 1
    int size;
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
