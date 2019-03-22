CFLAGS = -Werror -Wall -g3 -std=c99

#---------------------------------------------------------------
all: player clean cleanall


player.so: player.o
	gcc $^ -shared $@

player: player.o
	gcc -o $@ $^

player.o: player.c player.h
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------
test:


#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f player
