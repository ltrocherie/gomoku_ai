CFLAGS = -Werror -Wall -g3 -std=c99
SRC = server_bit  #game.o board.o bitboard.o

#---------------------------------------------------------------
all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------

bitboard.o: bitboard.c 
	gcc $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------

game_bit.o: game_bit.c 
	gcc $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------
move.o: move.c 
	gcc $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------

server_functions.o: server_functions.c 
	gcc -c ${CFLAGS} $< -o $@

server.o: server.c 
	gcc -c ${CFLAGS} $< -o $@

server_bit: server.o server_functions.o game_bit.o bitboard.o move.o
	gcc $^ -o $@ -ldl



#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
