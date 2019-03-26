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


#---------------------------------------------------------------
clean:
	(cd src && make clean)
	rm -f a.out *.o *# *~
	rm -f $(IST_DIR)/$(EXEC)
