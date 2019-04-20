CFLAGS = -Werror -Wall -g3 -std=c99
SRC = player_min_max.so #game.o board.o bitboard.o

#---------------------------------------------------------------
.PHONY = build clean cleanall

all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------
#Player compilation
player_min_max.so: player_min_max.o gamePM.o boardPM.o
	gcc $^ -shared -o $@

player_min_max: player_min_max.o gamePM.o boardPM.o
	gcc -o $@ $^

player_min_max.o: player_min_max.c 
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------
#Auxilary object files

gamePM.o:
	(cd ../board && make build)
	(cp ../board/game.o .)

boardPM.o:
	(cd ../board && make build)
	(cp ../board/board.o .)

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
