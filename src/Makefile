CFLAGS = -Werror -Wall -g3 -std=c99
SRC = server player1.so player2.so #game.o board.o bitboard.o

#---------------------------------------------------------------
all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------
#Player compilation
player.so: player.o
	gcc $^ -shared -o $@

player: player.o player.h move.h
	gcc -o $@ $^

player.o: player.c player.h
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------

bitboard.o: bitboard.c
	gcc $(CFLAGS) -c $^ -o $@

#---------------------------------------------------------------

game.o: game.c game.h board.h move.h
	gcc $(CFLAGS) -c $< -o $@


#---------------------------------------------------------------

board.o: board.c board.h move.h
	gcc ${CFLAGS} -c $< -o $@

#---------------------------------------------------------------
server.o: server.c game.h board.h player.h
	${CC} -c ${CFLAGS} $< -o $@

server: server.o player.o game.o board.o
	${CC} $^ -o $@ -ldl



#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f player player.so
