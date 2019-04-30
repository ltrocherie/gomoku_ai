SRC_DIR = src
TST_DIR = test
IST_DIR = install
EXEC = server
EXEC_BIT = server_bit
PLY = *.so

.PHONY:all test build install clean

#---------------------------------------------------------------
all: build install test clean

#---------------------------------------------------------------
exec:
	make clean
	make cleanall
	make install

#---------------------------------------------------------------
test:
	(cd $(TST_DIR) && make test)

#---------------------------------------------------------------
build:
	(cd $(SRC_DIR) && make build)


#---------------------------------------------------------------
install: 
	(cd $(SRC_DIR) && make install)
	cp ${SRC_DIR}/player.so ${IST_DIR}/player1.so
	cp ${SRC_DIR}/player.so ${IST_DIR}/player2.so
	cp ${SRC_DIR}/player_min_max.so ${IST_DIR}/player_min_max1.so
	cp ${SRC_DIR}/player_min_max.so ${IST_DIR}/player_min_max2.so
	cp ${SRC_DIR}/player_alpha_beta.so ${IST_DIR}/player_alpha_beta1.so
	cp ${SRC_DIR}/player_alpha_beta.so ${IST_DIR}/player_alpha_beta2.so
	(cd $(SRC_DIR) && mv $(EXEC) ../$(IST_DIR)/$(EXEC))
	(cd $(SRC_DIR) && mv $(EXEC_BIT) ../$(IST_DIR)/$(EX_TST))


#---------------------------------------------------------------
clean:
	(cd src && make clean)
	rm -f a.out *.o *# *~
cleanall:
	rm -f $(IST_DIR)/$(EXEC) $(IST_DIR)/$(EXEC_BIT) $(IST_DIR)/$(PLY)
	(cd $(SRC_DIR) && make cleanall)

