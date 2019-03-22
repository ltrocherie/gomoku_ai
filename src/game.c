#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 11

struct board{
  char m[MAX_SIZE][MAX_SIZE];
  int size;
};

struct board ini_game(int n)
{
  struct board bd;
  bd.winner = 0;
  bd.size = n;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      bd.m[i][j] = 0;
    }
  }
  return bd;
}

int place(struct board* bd, struct col_move_t col)
{
  if (!bd->m[col.m.row][col.m.col]) {
    bd->m[col.m.row][col.m.col] = col.c;
    return 0;
  }
  return -1;
}

int align(struct board const bd, struct col_move_t col)
{
    int max = 0;
    for (size_t dir = 0; dir < 4; dir++) {
        ij = 0;
        if (dir == 0){
            size_t i;
            for (i = 0; i < bd.size && i > 0; i++) {
                struct move_t cas = {col.m[0]+i, col.m[1]};//la case qu'on est en train de regarder
                if (color(cas) != col.c) {//si le pion sur la case n'est pas de la couleur du joueur qui nous intéresse
                    i--;
                    break;
                }
            }
            size_t j;
            for (j = 0; j < bd.size && j > 0; j++) {
                struct move_t cas = {col.m[0]-j, col.m[1]};//la case qu'on est en train de regarder
                if (color(cas) != col.c) {//si le pion sur la case n'est pas de la couleur du joueur qui nous intéresse
                    j--;
                    break;
                }
            }
            ij = i+j;
        }
        if (dir == 1){
            size_t i;#TODO
        }


        if (ij > max){
            max = ij;
        }
        //vérifier que chaque case testée est entre 0 et bd.size pour chacune de ses coordonnées
    }
}

int is_winning(struct board bd)
{
  return bd.winner;
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
