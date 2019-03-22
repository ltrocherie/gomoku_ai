CFLAGS = -Werror -Wall -g3 -std=c99

all: test_player clean cleanall

test_player: player.o test_player.o
	gcc -o $@ $^

player.o:
	(cd ../src/ && make player.o)
	(mv ../src/player.o .)

test_player.o: test_player.c
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f player
