CFLAGS = -Werror -Wall -g3 -std=c99
SRC = server #game.o board.o bitboard.o

#---------------------------------------------------------------
all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------

game.o: game.c 
	gcc $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------

board.o: board.c 
	gcc ${CFLAGS} -c $< -o $@

#---------------------------------------------------------------
move.o: move.c 
	gcc $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------

server_functions.o: server_functions.c 
	gcc -c ${CFLAGS} $< -o $@

server.o: server.c 
	gcc -c ${CFLAGS} $< -o $@

server: server.o server_functions.o game.o board.o move.o
	gcc $^ -o $@ -ldl

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
