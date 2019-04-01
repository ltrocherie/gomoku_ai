SRC_DIR = src
TST_DIR = test
IST_DIR = install
EXEC = server
PLY = *.so

.PHONY:all test build install clean

#---------------------------------------------------------------
all: build install test clean


#---------------------------------------------------------------
test:
	(cd $(TST_DIR) && make)

#---------------------------------------------------------------
build:
	(cd $(SRC_DIR) && make build)


#---------------------------------------------------------------
install: build
	cp ${SRC_DIR}/player.so ${IST_DIR}/player1.so
	cp ${SRC_DIR}/player.so ${IST_DIR}/player2.so
	(cd $(SRC_DIR) && mv server ../$(IST_DIR)/$(EXEC))


#---------------------------------------------------------------
clean:
	(cd src && make clean)
	rm -f a.out *.o *# *~
cleanall:
	rm -f $(IST_DIR)/$(EXEC) $(IST_DIR)/$(PLY)
	(cd $(SRC_DIR) && make cleanall)

