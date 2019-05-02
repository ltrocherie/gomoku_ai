CFLAGS = -Werror -Wall -g3 -std=c99
SRC = player_min_max.so #player_min_max.o #game.o board.o bitboard.o

#---------------------------------------------------------------
.PHONY = build clean cleanall

all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------
#Player compilation
player_min_max.so: player_min_max.o boardPM.o gamePM.o  
	gcc $^ -shared -o $@

player_min_max: player_min_max.o ../server_dir/game.o ../server_dir/board.o
	gcc -o $@ $^

player_min_max.o: player_min_max.c 
	gcc ${CFLAGS} -c -fPIC $< -o $@

boardPM.o: boardPM.c
	gcc ${CFLAGS} -c -fPIC $< -o $@

gamePM.o: gamePM.c
	gcc ${CFLAGS} -c -fPIC $< -o $@
#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
