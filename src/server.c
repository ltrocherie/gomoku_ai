#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>
#include <getopt.h>
#include "game.h"
#include "server.h"

// fonction pour trier les arguments de la ligne de commande
int parse_opts( int argc, char* argv[] ) {
  int opt;
  while ( ( opt = getopt( argc, argv, "n:" ) ) != -1 ) {
    switch ( opt ) {
    case 'n':
      BOARD_SIZE = atoi( optarg );
      break;
    default: /* '?' */
      fprintf( stderr, "Usage: %s [-n BOARD_SIZE] \n",
	       argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  return optind;
}


int main(int argc, char* argv[])
{
  struct col_move_t moves;
  void* players_libs[MAX_PLAYERS];
  size_t board_size = 0;
  int swap_mode = 0;
  parse_arg(argc, argv,&board_size, &swap_mode, players_libs);
  if(error_management(&board_size,players_libs))
    exit(1);
  struct player players[MAX_PLAYERS];
  struct player first_player = players[0];
  struct player second_player = players[1];
  initialise_players_data(players, players_libs);
  if(swap_mode)
    activate_swap_mod(&moves,board_size, first_player, second_player);
  //TODO boucle de jeu   
  close_libs(players_libs);
  return 0;
}
