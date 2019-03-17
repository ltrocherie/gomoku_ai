#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>
#include "game.h"


#define MAX_PLAYERS 4

int main(int argc, char* argv[])
{
  void* players_libs[MAX_PLAYERS];
  parse_arg(argc, argv,players_libs);
  if( error_management(players_libs))
    exit(1);
  struct player players[MAX_PLAYERS];
  initialise_players_data(players, players_libs);
      /*
  char const* (*get_player_name)(void);
  get_player_name = dlsym(lib_player,"get_player_name");
  printf("%s\n", (*get_player_name)());
      */
  close_libs(players_libs);
  return 0;
}
