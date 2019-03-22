#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <assert.h>
#include <getopt.h>
#include <unistd.h>
#include "move.h"
#include "board.h"
#include "game.h"
#include "player.h"

struct player{
  char const * name;
  enum color_t color;
  size_t n_moves;
  char const* (*get_player_name)();
  struct col_move_t* (*propose_opening)(size_t size);
  int (*accept_opening)(size_t size, const struct col_move_t* opening);
  void (*initialize)(size_t size, enum color_t id);
  struct move_t (*play)(struct col_move_t const previous_moves[], size_t n_moves);
  void (*finalize)();
};


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
	  (*board_size) = (size_t)optarg;
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

int error_management(size_t* board_size, void* players_libs[])
{
  if(!board_size)
    return 1;
  for(int i=0; i<NB_PLAYERS; i++)
    {
      if(!players_libs[i])
	{
	  fputs (dlerror(), stderr);
	  return 1;
	}
    }
  return 0;
}

void initialize_players_data(struct player players[], void* players_libs[])
{
  for(int i=0; i<NB_PLAYERS; i++)
    {
      players[i].color = i;
      players[i].get_player_name = dlsym(players_libs[i],"get_player_name");
      if(dlerror() != NULL)
	{
	  fputs(dlerror(), stderr);
	  exit(1);
	}
      players[i].propose_opening = dlsym(players_libs[i],"propose_opening");
      if(dlerror() != NULL)
	{
	  fputs(dlerror(), stderr);
	  exit(1);
	}
      players[i].accept_opening = dlsym(players_libs[i],"accept_opening");
      if(dlerror() != NULL)
	{
	  fputs(dlerror(), stderr);
	  exit(1);
	}
      players[i].initialize = dlsym(players_libs[i],"initialize");
      if(dlerror() != NULL)
	{
	  fputs(dlerror(), stderr);
	  exit(1);
	}
      players[i].play = dlsym(players_libs[i],"play");
      if(dlerror() != NULL)
	{
	  fputs(dlerror(), stderr);
	  exit(1);
	}
      players[i].finalize = dlsym(players_libs[i],"finalize");
      if(dlerror() != NULL)
	{
	  fputs(dlerror(), stderr);
	  exit(1);
	}
      players[i].name = (players[i].get_player_name)();
    }
}

void activate_swap_mode(struct col_move_t* moves, size_t board_size, struct player players[])
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
}
   
void close_libs(void* players_libs[])
{
  for(int i=0; i<NB_PLAYERS; i++)
    dlclose(players_libs[i]);
}

void enqueue(struct col_move_t* moves,
int main(int argc, char* argv[])
{
  void* players_libs[NB_PLAYERS];
  size_t board_size = 0;
  int swap_mode = 0;
  
  parse_arg(argc, argv,&board_size, &swap_mode, players_libs);
  if(error_management(&board_size,players_libs))
    exit(1);
 
  struct player players[NB_PLAYERS];
  initialize_players_data(players, players_libs);

  struct board board = ini_game(board_size);
  struct col_move_t moves[NB_PLAYERS+2];
  struct move_t m;
  struct col_move_t col_m;
  if(swap_mode)
    {
      activate_swap_mode(moves,board_size, players);
      m =(players[1].play)(moves,3);
      enqueue(m, moves,3);
      m=(players[0].play)(moves,4);
      enqueue(m,moves,4);
      m=(players[1].play)(moves,2);
      enqueue(m,moves,2);
    }
  while(1)
    {
      for(int i=0; i<NB_PLAYERS; i++)
	{
	  m = (players[i].play)(moves,NB_PLAYERS);
	  col_m.m = m;
	  col_m.c = players[i].color;
	  place(&board, col_m);
	  if(is_winning(board, col_m) == -1)
	    break;
	  enqueue(m,&moves);
	}
      
    }
  finalize(players);
  close_libs(players_libs);
  return 0;
}
