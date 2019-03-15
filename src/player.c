#include<stdio.h>

#define MAX_NAME_LENGTH

char const* get_player_name(){
  char const name[MAX_NAME_LENGTH] = malloc(MAX_NAME_LENGTH * sizeof(char));
  scanf("[a-zA-Z0-9 -_]%s", name);
  return name;
};

