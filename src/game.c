#include <stdio.h>
#include <stdlib.h>
#include "move.h"

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
  int max = 0;
  for (size_t dir=0;dir<;dir++){
    size_t i = cm.m.row, j = cm.m.col;  

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
	else                        //dessous à droite
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

//renvoie l'entier associé au gagnant s'il y en a un apres le move cm
//renvoie l'entier associé au perdant + 4 s'il y en a un après le move cm 
//renvoie -1 s'il n'y a ni gagnant ni perdant
int is_winning(struct board bd, struct col_move_t cm)
{
  if (align(bd, cm) == 5)
    return cm.c;
  if (align(bd, cm) > 5)
    return cm.c+4;
  return -1;
}

void parse_arg(int argc, char* argv[], size_t* board_size, int* swap_mode, void* players_libs[])
{                   
  if(argc <= 1)
    {
      printf( "at least one argument is required\n" );
      exit(EXIT_SUCCESS);
    }
  int opt;
  while ((opt = getopt(argc, argv, "no:")) != -1)
    {
      switch (opt)
	{
	case 'n':
	  *board_size = optarg;
	case 'o':
	  *swap_mode = 1;
	default:
	  fprintf(stderr, "Unknown character\n");
	  exit(EXIT_FAILURE);
	}
    }
  if (optind >= argc)
    {
      fprintf(stderr, "Expected argument after options\n");
      exit(EXIT_SUCCESS);
    }
  for(int index = optind; index<argc; index++)
    *(players_libs+index) = argv[index];
}

int error_management(size_t board_size, void* players_libs[])
{
  if(!board_size)
    return 1;
  for(int i=0; i<MAX_PLAYERS; i++)
    {
      if(!players_libs[i])
	{
	  fputs (dlerror(), stderr);
	  return 1;
	}
    }
  return 0;
}

void initialise_players_data(struct player players[], void* players_libs[])
{
  for(int i=0; i<MAX_PLAYERS; i++)
    {
      players[i].color = i;
      players[i].get_player_name = dlsym(players_libs[i],"get_player_name");
      if(dlerror != NULL)
	{
	  fputs(dlerror, stderr);
	  exit(1);
	}
      players[i].propose_opening = dlsym(players_libs[i],"propose_opening");
      if(dlerror != NULL)
	{
	  fputs(dlerror, stderr);
	  exit(1);
	}
      players[i].accept_opening = dlsym(players_libs[i],"accept_opening");
      if(dlerror != NULL)
	{
	  fputs(dlerror, stderr);
	  exit(1);
	}
      players[i].initialize = dlsym(players_libs[i],"initialize");
      if(dlerror != NULL)
	{
	  fputs(dlerror, stderr);
	  exit(1);
	}
      players[i].play = dlsym(players_libs[i],"play");
      if(dlerror != NULL)
	{
	  fputs(dlerror, stderr);
	  exit(1);
	}
      players[i].finalize = dlsym(players_libs[i],"finalize");
      if(dlerror != NULL)
	{
	  fputs(dlerror, stderr);
	  exit(1);
	}
      players[i].name = *(players[i].get_player_name)();
    }
}

void activate_swap_mode(struct col_move_t* moves, size_t board_size, struct player* first_player, struct player* first_player)
{
  *moves = first_player->propose_opening(board_size);
  if(second_player->accept_opening(board_size,moves));
  {
    (*first_player)->initialize(board_size, BLACK);
    (*second_player)->initialize(board_size, WHITE);
  }
  else
    {
      (*first_player)->initialize(board_size, WHITE);
      (*second_player)->initialize(board_size, BLACK);
    }
}
   
void close_libs(void* players_libs[])
{
  for(int i=0; i<MAX_PLAYERS; i++)
    dlclose(players_libs[i]);
}
