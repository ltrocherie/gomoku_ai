CFLAGS = -Werror -Wall -g3 -std=c99

all: player.o clean


player.so: player.o
	gcc $^ -shared $@

player.o: player.c
	gcc $(CFLAGS) -c -fPIC $^ -o $@

clean:
	rm -f *.o *~
