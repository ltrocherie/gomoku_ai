CFLAGS = -Werror -Wall -g3 -std=c99
SRC = bitboard.o  #game.o board.o bitboard.o

#---------------------------------------------------------------
all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------

bitboard.o: bitboard.c
	gcc $(CFLAGS) -c $< -o $@


#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
