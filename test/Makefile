CFLAGS = -Werror -Wall -g3 -std=c99

all: test_player

test_player: player.o test_player.o
	gcc -o $@ $^

clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f player
