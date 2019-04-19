#include<stdio.h>
#include<stdlib.h>

#include "player_min_max.h"

#define MAX_NAME_LENGTH 10
#define NB_OPENING_MOVE 3
static struct board* my_testing_board;
//struct col_move_t all_moves[BOARD_SIZE*BOARD_SIZE];


/*
  These functions are public. The description of the functions
  is in player.h
 */
//char* names[2] = {"random1", "random2"};

int belongs(struct col_move_t const tab[], struct move_t mv, size_t n);

char const *get_player_name(){
  char *name;
  name = "random";
  return name;
}

struct col_move_t* propose_opening(size_t size){
  struct col_move_t *move = malloc(100 * sizeof(struct col_move_t));
  for(int i = 0; i<NB_OPENING_MOVE; i++){
    struct move_t mv;
    mv.row = rand()%size;
    mv.col = rand()%size;
    struct col_move_t mv_next;
    mv_next.m = mv;
    mv_next.c = i%2;
    if(!belongs(move, mv, i))
      move[i] = mv_next;
    else
      i--;
  }
  return move;
}

int accept_opening(size_t size, const struct col_move_t* opening){
  return 1;
}


void initialize(size_t size, enum color_t id){
  my_testing_board = malloc(sizeof(struct board));
  *my_testing_board = ini_board(size);
  all_moves = malloc(sizeof(struct col_move_t));
  all_moves_size = 0;
  BOARD_SIZE = size;
  PLAYER_COLOR = id;
  srand(42);
  return;
}

int belongs(struct col_move_t const tab[], struct move_t mv, size_t n){
  if(n != 0)
    {
      for(size_t i=0; i < n; i++){
	if(mv.row == tab[i].m.row && mv.col == tab[i].m.col)
	  return 1;
      }
    }
  return 0;
}

int min(struct board* bd, enum color_t my_color, enum color_t ad_color, int step, struct col_move_t cm, int board_free_place);
int max(struct board* bd, enum color_t my_color, enum color_t ad_color, int step, struct col_move_t cm, int board_free_place);

int min(struct board* bd, enum color_t my_color, enum color_t ad_color, int step, struct col_move_t cm, int board_free_place)
{
  //printf("min %ld%ld", cm.m.row, cm.m.col);
  if (step>2)
    return 0;
  struct col_move_t simul_move;
  int res;
  int min = 1000;
  int win = is_winning(*bd, cm);
  if(win != -1)
    return min;
  if (!board_free_place)
    return 0;
  for(size_t i=0; i<BOARD_SIZE; i++)
    {
      for(size_t j=0; j<BOARD_SIZE; j++)
	{
	  if (bd->m[i][j] == -1)
	    {
	      bd->m[i][j] = ad_color;
	      simul_move.m.row = i;
	      simul_move.m.col = j;
	      simul_move.c = ad_color;
	      res = max(my_testing_board, my_color, ad_color, step+1, simul_move,board_free_place-1); //faire current move
	      if (res < min)
		min = res;
	      my_testing_board->m[i][j] = -1;
	    }
	}
    }
   return min;
}

int max(struct board* bd, enum color_t my_color, enum color_t ad_color, int step, struct col_move_t cm, int board_free_place)
{
  //printf("max %ld%ld", cm.m.row, cm.m.col);
  struct col_move_t simul_move;
  int res;
  int max = -1000;
  int win = is_winning(*bd, cm);
  if(win != -1)
    return max*step;
  if (!board_free_place)
    return 0;
  for(size_t i=0; i<BOARD_SIZE; i++)
    {
      for(size_t j=0; j<BOARD_SIZE; j++)
	{
	  if (bd->m[i][j] == -1)
	    {
	      bd->m[i][j] = my_color;
	      simul_move.m.row = i;
	      simul_move.m.col = j;
	      simul_move.c = ad_color;
	      res = min(my_testing_board, my_color, ad_color, step+1, simul_move, board_free_place-1); //faire current move
	      if (res > max)
		max = res;
	      my_testing_board->m[i][j] = -1;
	    }
	  
	}
    }
   return max;
}


struct move_t play(struct col_move_t previous_moves[],size_t n_moves){

  //printf("%ld\n", n_moves);
  for(size_t i=0; i<n_moves; i++)
    place(my_testing_board, previous_moves[i]);
  //for (size_t i = 0; i < n_moves; i++)
  //{
  //  all_moves[all_moves_size] = previous_moves[i];
  //  all_moves_size++;
  //}
  
  struct move_t next_move = {0,0};
  struct col_move_t simul_move;
  int simul_result;
  int max = -100000;
  int board_free_place = BOARD_SIZE*BOARD_SIZE-all_moves_size;
  enum color_t ENNEMIE_COLOR = previous_moves[n_moves-1].c;
  // printf("%ld\n", BOARD_SIZE);
  for(size_t i=0; i<BOARD_SIZE; i++)
    {
      printf("OK\n");
      for(size_t j=0; j<BOARD_SIZE; j++)
	{
	  printf("%ld %ld %d\n",i,j, my_testing_board->m[i][j]);
	  if (my_testing_board->m[i][j] == -1)
	    {
	      simul_move.m.row = i;
	      simul_move.m.col = j;
	      simul_move.c = PLAYER_COLOR;
	      place(my_testing_board,simul_move);
	      simul_result = min(my_testing_board, PLAYER_COLOR, ENNEMIE_COLOR, 1 , simul_move, board_free_place-1); //todo simul_mov et simul_result
	      //	      printf("%d\n", simul_result);
	      if (simul_result > max)
		{
		  max = simul_result;
		  next_move = simul_move.m;
		}
	      my_testing_board->m[i][j] = -1;
	    }
	}
    }
  //printf("%d\n",max);
  printf("Je place mon pion en %ld %ld !\n", next_move.row, next_move.col);
  return next_move;
}

void finalize(){
  free(all_moves);
  free(my_testing_board);
  return;
}


