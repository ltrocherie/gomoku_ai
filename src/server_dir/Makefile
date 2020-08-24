CFLAGS = -Werror -Wall -g3 -std=c99
SRC = server server_bit#game.o board.o bitboard.o

.PHONY: $(SRC) clean cleanall

build: $(SRC)

#---------------------------------------------------------------
move.o: move.c
	gcc $(CFLAGS) -c $< -o $@

#---------------------------------------------------------------

game.o: game.c
	gcc $(CFLAGS) -c $< -o $@

game_bit.o: game.c
	gcc $(CFLAGS) -DB -c $< -o $@

board.o:
	(cd ../board && make build)
	(mv ../board/$@ .)

bitboard.o:
	(cd ../bitboard && make build)
	(mv ../bitboard/$@ .)

#---------------------------------------------------------------

server_functions.o: server_functions.c
	gcc -c ${CFLAGS} $< -o $@

server.o: server.c
	gcc -c ${CFLAGS} $< -o $@

server: server.o server_functions.o game.o board.o move.o
	gcc $^ -o $@ -ldl

server_bit: server.o server_functions.o game_bit.o bitboard.o move.o
	gcc $^ -o $@ -ldl

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
