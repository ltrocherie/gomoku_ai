all: player.o clean


player.so: player.o
	gcc $^ -shared $@

player.o: player.c
	gcc -c -fPIC $^ -o $@

clean:
	rm -f *.o *~
