#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>
#include <getopt.h>
#include <unistd.h>
#include "server_functions.h"

//  parse_arg balaye la ligne de commande en effectuant un parse-opt 
// puis recupere les bibliotheques des joueurs

void parse_arg(int argc, char* argv[], size_t* board_size, int* swap_mode, void* players_libs[])
{
  if(argc <= 1)
    {
      printf( "at least one argument is required\n" );
      exit(EXIT_SUCCESS);
    }
  int opt;
  while ( ((opt = getopt(argc, argv, "on:")) != -1))
    {
      switch (opt)
	{
	case 'n':
	  (*board_size) =(size_t)atoi(optarg);
	  break;
	case 'o':
	  (*swap_mode) = 1;
	  break;
	case '?':
	  fprintf(stderr, "Usage: %s [-s nsecs] name\n", argv[0]);
	  exit(EXIT_FAILURE);
	} 
    }
  if (optind >= argc)
   {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_SUCCESS);
   }

  for(int i = 0; i<NB_PLAYERS; i++)
    {
      printf("\n");
      players_libs[i] = dlopen(argv[optind+i], RTLD_LAZY);
    }
}

/*
  retourne 1 si la taille du board fournie sur la ligne de commande est null
  ou si les bibliotheques fournie sont inexistantes
*/
int error_management(size_t board_size, void* players_libs[])
{
  if(!board_size)
    return 1;
  for(int i=0; i<NB_PLAYERS; i++)
    {
      if((players_libs[i]) == NULL)
	return 1;
    }
  return 0;
}

/*
  la fonction suivante initialise les joueurs presents en recuperant leurs donnees
   dans les bibliotheques assosciees
*/
void initialize_players_data(struct player* players, void* players_libs[])
{
  for(int i=0; i<NB_PLAYERS; i++)
      {
	players[i].color = i;
	players[i].get_player_name = dlsym(players_libs[0],"get_player_name");
	if(players[i].get_player_name == NULL)
	  exit(1);
	players[i].propose_opening = dlsym(players_libs[i],"propose_opening");
	if(players[i].propose_opening == NULL)
	  exit(2);
	players[i].accept_opening = dlsym(players_libs[i],"accept_opening");
	if(players[i].accept_opening == NULL)
	  exit(3);
	players[i].initialize = dlsym(players_libs[i],"initialize");
	if(players[i].initialize == NULL)
	  exit(4);
	players[i].play = dlsym(players_libs[i],"play");
	if(players[i].play == NULL)
	  exit(5);
	players[i].finalize = dlsym(players_libs[i],"finalize");
	if(players[i].finalize == NULL)
	  exit(6);
players[i].name = (players[i].get_player_name)();
      }
}

/*
  cette donction active le mode swap quand la demande est faite sur la ligne de commande 
 et fait 3 tours de jeux pour revenir à une situation comme sans swap. Cela permet que la
 boucle de jeu dans le main soit la meme avec ou sans swap
*/
void activate_swap_mode(struct col_move_t* moves, size_t* n_moves, size_t board_size, struct player players[])
{
  moves = players[0].propose_opening(board_size);
  if((players[1].accept_opening)(board_size,moves))
    {
      (players[0].initialize)(board_size, BLACK);
      (players[1].initialize)(board_size, WHITE);
    }
  else
    {
      (players[0].initialize)(board_size, WHITE);
      (players[1].initialize)(board_size, BLACK);
    }
   struct col_move_t col_m;
   struct move_t m;
   *n_moves = NB_PLAYERS+1;
   m =(players[1].play)(moves,*n_moves);
   col_m.m = m;
   col_m.c = players[1].color;
   enqueue(col_m, moves,n_moves);
   m=(players[0].play)(moves,*n_moves);
   col_m.m = m;
   col_m.c = players[0].color;
   enqueue(col_m,moves,n_moves);
   m=(players[1].play)(moves,*n_moves);
   col_m.m = m;
   col_m.c = players[1].color;
   enqueue(col_m,moves,n_moves);
}

/*
  A la fin du jeu cette fonction clot toutes les bibliotheques ouvertes au debut
*/
void close_libs(void* players_libs[])
{
  for(int i=0; i<NB_PLAYERS; i++)
    dlclose(players_libs[i]);
}
