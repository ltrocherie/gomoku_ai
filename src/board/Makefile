CFLAGS = -Werror -Wall -g3 -std=c99
SRC = board.o
#---------------------------------------------------------------
all: build clean cleanall

build: $(SRC)

#---------------------------------------------------------------

board.o: board.c
	gcc ${CFLAGS} -c $< -o $@

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
