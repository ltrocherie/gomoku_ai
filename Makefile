<<<<<<< HEAD
SRC_DIR=src
INSTALL_DIR=install

CC=cc
CFLAGS= -std=c99 -Wall

.PHONY:all test build install clean

#---------------------------------------------------------------
all: build install test


#---------------------------------------------------------------
test: build
	./${INSTALL_DIR}/server -n 5 -o ${INSTALL_DIR}/player1.so ${INSTALL_DIR}/player2.so


#---------------------------------------------------------------
build: server player1.so player2.so


#---------------------------------------------------------------
install:build
	cp server ${INSTALL_DIR}/server
	cp player1.so ${INSTALL_DIR}/player1.so
	cp player2.so ${INSTALL_DIR}/player2.so
=======
SRC_DIR = src
TST_DIR = test
IST_DIR = install
EXEC = server

#---------------------------------------------------------------
all: test build install clean


#---------------------------------------------------------------
test:
	(cd $(TST_DIR) && make test)

#---------------------------------------------------------------
build:
	(cd $(SRC_DIR) && make build)


#---------------------------------------------------------------
install:
	(cd $(SRC_DIR) && cp player.so ../$(IST_DIR)/player1.so)
	(cd $(SRC_DIR) && cp player.so ../$(IST_DIR)/player2.so)
	(cd $(SRC_DIR) && mv ./server ../$(IST_DIR)/$(EXEC))
>>>>>>> refs/remotes/origin/master


#---------------------------------------------------------------
clean:
	(cd src && make clean)
	rm -f a.out *.o *# *~
<<<<<<< HEAD

board.o: ${SRC_DIR}/board.c ${SRC_DIR}/board.h ${SRC_DIR}/move.h
	${CC} -c ${CFLAGS} $< -o $@

game.o: ${SRC_DIR}/game.c ${SRC_DIR}/game.h ${SRC_DIR}/board.h ${SRC_DIR}/move.h
	${CC} -c ${CFLAGS} $< -o $@

player.o: ${SRC_DIR}/player.c ${SRC_DIR}/player.h ${SRC_DIR}/move.h
	${CC} -c -fPIC ${CFLAGS} $< -o $@

player1.so: player.o
	gcc -shared -o $@ $<

player2.so: player.o
	gcc -shared -o $@ $<

server.o: ${SRC_DIR}/server.c ${SRC_DIR}/game.h ${SRC_DIR}/board.h ${SRC_DIR}/player.h
	${CC} -c ${CFLAGS} $< -o $@

server: server.o player.o game.o board.o
	${CC} $^ -o $@ -ldl



=======
	rm -f $(IST_DIR)/$(EXEC)
>>>>>>> refs/remotes/origin/master
