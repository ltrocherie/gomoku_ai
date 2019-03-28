CFLAGS = -Werror -Wall -g3 -std=c99
SRC = player.o #game.o board.o bitboard.o

#---------------------------------------------------------------
all: build clean cleanall

build: $(SRC)


#---------------------------------------------------------------
#Player compilation
player.so: player.o
	gcc $^ -shared -o $@

player: player.o
	gcc -o $@ $^

player.o: player.c player.h
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------

bitboard.o: bitboard.c
	gcc $(CFLAGS) -c $^ -o $@

#---------------------------------------------------------------

game.o: game.c
	gcc $(CFLAGS) -c $^ -o $@


#---------------------------------------------------------------

board.o: board.c
	gcc $(CFLAGS) -c $^ -o $@

#---------------------------------------------------------------



#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f player player.so
