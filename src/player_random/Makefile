CFLAGS = -Werror -Wall -g3 -std=c99
SRC = player.so #game.o board.o bitboard.o

#---------------------------------------------------------------
all: build clean cleanall

build: player.so

#---------------------------------------------------------------
#Player compilation
player.so: player.o
	gcc $^ -shared -o $@

player: player.o 
	gcc -o $@ $^

player.o: player.c 
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
