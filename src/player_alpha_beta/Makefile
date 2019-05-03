CFLAGS = -Werror -Wall -g3 -std=c99
SRC = player_alpha_beta.so #player_alpha_beta_bad.so #game.o board.o bitboard.o #game.o board.o bitboard.o

#---------------------------------------------------------------
.PHONY = build clean cleanall

all: build clean cleanall

build: ${SRC}

#---------------------------------------------------------------
#Player compilation
player_alpha_beta.so: player_alpha_beta.o boardAB.o gameAB.o
	gcc $^ -shared -o $@

player_alpha_beta.o: player_alpha_beta.c 
	gcc ${CFLAGS} -c -fPIC $< -o $@

#player_alpha_beta_bad.so: player_alpha_beta_bad.o boardAB.o gameAB.o
#	gcc $^ -shared -o $@

#player_alpha_beta_bad.o: player_alpha_beta_bad.c 
#	gcc ${CFLAGS} -c -fPIC $< -o $@


boardAB.o: ../board/board.c
	gcc ${CFLAGS} -c -fPIC $< -o $@

gameAB.o: ../server_dir/game.c
	gcc ${CFLAGS} -c -fPIC $< -o $@

#---------------------------------------------------------------
clean:
	rm -f a.out *.o *# *~

cleanall:
	rm -f $(SRC)
