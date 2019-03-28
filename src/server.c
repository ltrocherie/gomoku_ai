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

#define _GNU_SOURCE

struct player{
  char const* name;
  enum color_t color;
  size_t n_moves;
  char const* (*get_player_name)(int i);
  struct col_move_t* (*propose_opening)(size_t size);
  int (*accept_opening)(size_t size, const struct col_move_t* opening);
  void (*initialize)(size_t size, enum color_t id);
  struct move_t (*play)(struct col_move_t const previous_moves[], size_t n_moves);
  void (*finalize)();
};

void parse_arg(int argc, char* argv[], size_t* board_size, int* swap_mode, void* players_libs[])
{
  //extern char *optarg;
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
	  //  printf("%ld\n",*board_size);
	  break;
	case 'o':
	  (*swap_mode) = 1;
	  // printf("%d\n", *swap_mode);
	  break;
	case '?':
	  fprintf(stderr, "Usage: %s [-s nsecs] name\n", argv[0]);
	  exit(EXIT_FAILURE);
	}
      
    }
  //printf("%d\n", optind);
  if (optind >= argc)
   {
    fprintf(stderr, "Expected argument after options\n");
    exit(EXIT_SUCCESS);
   }
  for(int i = 0; i<NB_PLAYERS; i++)
  {
      
    players_libs[i] = dlopen(argv[optind+i], RTLD_NOW);
    // printf("%p\n", players_libs[i]);
  }
  //printf("Ok\n");
}

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
	players[i].name = (players[i].get_player_name)(i);
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


void enqueue(struct col_move_t m, struct col_move_t moves[], size_t* n_moves)
{
  if(*n_moves != NB_PLAYERS && *n_moves != 2*NB_PLAYERS)
    {
      moves[*n_moves] = m;
      *n_moves += 1;
    }
  else
    {
      for(int i=0; i<NB_PLAYERS-1;i++)
	{
	  moves[i] = moves[*n_moves-NB_PLAYERS+1+i];
	  moves[NB_PLAYERS-1] = m;
	  *n_moves = NB_PLAYERS;
	}
    }
}

int main(int argc, char* argv[])
{
  void* players_libs[NB_PLAYERS];
  size_t board_size = 10;
  int swap_mode = 0;
  parse_arg(argc, argv,&board_size, &swap_mode, players_libs);

  if(error_management(board_size,players_libs))
    exit(1);
  struct player* players = malloc(2*sizeof(struct player));
  initialize_players_data(players, players_libs);
  struct board board = ini_board(board_size);
  struct col_move_t moves[NB_PLAYERS+2];
  struct move_t m;
  struct col_move_t col_m;
  size_t n_moves = 0;
  int res;
  if(swap_mode)
    {
      n_moves = NB_PLAYERS+1;
      activate_swap_mode(moves,board_size, players);
      m =(players[1].play)(moves,n_moves);
      col_m.m = m;
      col_m.c = players[1].color;
      
      //printf("%ld\n", m.row);
      //printf("%ld\n", m.col);
      //printf("%d\n", col_m.c);
      enqueue(col_m, moves,&n_moves);
      m=(players[0].play)(moves,n_moves);
      col_m.m = m;
      col_m.c = players[0].color;
      
      //printf("%ld\n", m.row);
      //printf("%ld\n", m.col);
      // printf("%d\n", col_m.c);
      enqueue(col_m,moves,&n_moves);
      m=(players[1].play)(moves,n_moves);
      col_m.m = m;
      col_m.c = players[1].color;
      enqueue(col_m,moves,&n_moves);
    }
  //printf("OK\n");
  while(1)
  {
    for(int i=0; i<NB_PLAYERS; i++)
  	{
	  m = (players[i].play)(moves,n_moves);
	  col_m.m = m;
	  //printf("%ld\n", m.row);
	  // printf("%ld\n", m.col);
	  col_m.c = players[0].color;
	  // printf("%d\n", col_m.c);
       
	  place(&board, col_m);
	  res = is_winning(board, col_m);
	  if(res != -1)
	    break;
	  enqueue(col_m,moves,&n_moves);
	}
    if(res<NB_PLAYERS)
      break;
    //TODO function eliminate    
  }
  printf("Player %d is winner \n",res);
  //finalize();
  close_libs(players_libs);
  //  printf("OKK\n");
  return 0;
}


