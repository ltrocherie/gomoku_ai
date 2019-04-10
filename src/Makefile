CFLAGS = -Werror -Wall -g3 -std=c99
EX_DIR = board
EX_BIT_DIR = bitboard
PL_DIR = player_random
EX = server
EX_BIT = server_bit
PL = player.so


#---------------------------------------------------------------
.PHONY: all build install clean cleanall

all: build install clean cleanall

build:
	(cd $(EX_DIR) && make build)
	(cd $(EX_BIT_DIR) && make build)
	(cd $(PL_DIR) && make build)

install: build
	(cd $(EX_DIR)/ && mv $(EX) ../)
	(cd $(EX_BIT_DIR)/ && mv $(EX_BIT) ../)
	(cd $(PL_DIR)/ && mv $(PL) ../)


clean:
	rm -f a.out *.o *# *~
	(cd $(EX_DIR) && make clean)
	(cd $(EX_BIT_DIR) && make clean)
	(cd $(PL_DIR) && make clean)


cleanall:
	(cd $(EX_DIR) && make cleanall)
	(cd $(EX_BIT_DIR) && make cleanall)
	(cd $(PL_DIR) && make cleanall)
	rm -f $(EX) $(EX_BIT) $(PL)
