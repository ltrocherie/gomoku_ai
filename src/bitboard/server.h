#ifndef _SERVER_H_
#define _SERVER_H_

struct player{
  char * name;
  enum color_t color;
  struct col_move_t const previous_moves[];
  size_t n_moves;
  char const* (*get_player_name)();
  struct col_move_t* (*propose_opening)(size_t size);
  int (*accept_opening)(size_t size, const struct col_move_t* opening);
  void (*initialize)(size_t size, enum color_t id);
  struct move_t (*play)(struct col_move_t const previous_moves[], size_t n_moves);
  void (*finalize)();
};

#endif
