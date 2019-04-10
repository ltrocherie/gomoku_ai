CFLAGS = -Werror -Wall -g3 -std=c99
PL = player_random
TST = test_player

all:clean test_player cleanall

test: test_player
	./$(TST)

test_player: player.o test_player.o
	gcc -o $@ $^

player.o:
	(cd ../src/$(PL)/ && make player.o)
	(mv ../src/$(PL)/player.o .)

test_player.o: test_player.c
	gcc $(CFLAGS) -c $^ -o $@


#test_game: board.o game.o test_game.o

#board.o:
#	(cd ../src/ && make player.o)
#	(mv ../src/player.o .)

#test_player.o: test_player.c
#	gcc $(CFLAGS) -c $^ -o $@



clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(TST)
