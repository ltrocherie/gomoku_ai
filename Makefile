SRC_DIR = src
TST_DIR = test
IST_DIR = install
EXEC = server
EX_TST = server_bit
PLY = *.so

.PHONY:all test build install clean

#---------------------------------------------------------------
all: build install test clean

#---------------------------------------------------------------
exec:
	make cleanall
	make install

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
	(cd $(SRC_DIR) && mv $(EXEC) ../$(IST_DIR)/$(EXEC))
	(cd $(SRC_DIR) && mv $(EX_TST) ../$(IST_DIR)/$(EX_TST))


#---------------------------------------------------------------
clean:
	(cd src && make clean)
	rm -f a.out *.o *# *~
cleanall:
	rm -f $(IST_DIR)/$(EXEC) $(IST_DIR)/$(PLY)
	(cd $(SRC_DIR) && make cleanall)

