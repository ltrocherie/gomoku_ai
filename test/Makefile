CFLAGS = -Werror -Wall -g3 -std=c99

all:clean test_player cleanall

test_player: player.o test_player.o
	gcc -o $@ $^

player.o:
	(cd ../src/ && make player.o)
	(mv ../src/player.o .)

test_player.o: test_player.c
	gcc $(CFLAGS) -c $^ -o $@

"/
test_game: board.o game.o test_game.o

board.o:
	(cd ../src/ && make player.o)
	(mv ../src/player.o .)

test_player.o: test_player.c
	gcc $(CFLAGS) -c $^ -o $@

/"

clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f player
