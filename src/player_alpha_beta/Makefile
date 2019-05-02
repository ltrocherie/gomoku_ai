CFLAGS = -Werror -Wall -g3 -std=c99
SRC = player_alpha_beta.so #game.o board.o bitboard.o

#---------------------------------------------------------------
.PHONY = build clean cleanall

all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------
#Player compilation
player_alpha_beta.so: player_alpha_beta.o ../server_dir/game.o ../server_dir/board.o
	gcc $^ -shared -o $@

player_alpha_beta: player_alpha_beta.o ../server_dir/game.o ../server_dir/board.o
	gcc -o $@ $^

player_alpha_beta.o: player_alpha_beta.c 
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
