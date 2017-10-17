# criar pasta /lib neste diretório para funcionar este makefile


CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
CFLAGS=-c

all: libcthread

libcthread: insert.o escalonador.o cthread.o
	mv *.o $(BIN_DIR)
	ar rcs $(LIB_DIR)/libmthread.a $(BIN_DIR)/insert.o $(BIN_DIR)/escalonador.o $(BIN_DIR)/cthread.o

insert.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/insert.c 

escalonador.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/escalonador.c 

cthread.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/cthread.c 

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~


