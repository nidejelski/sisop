# criar pasta /lib neste diretório para funcionar este makefile
# gcc src/main.c src/hello.c -o main -I"../include"  


CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
CFLAGS=-c

all: libcthread

libcthread: escalonador.o cthread.o filas.o tcb.o
	mv *.o $(BIN_DIR)
	ar rcs $(LIB_DIR)/libcthread.a $(BIN_DIR)/escalonador.o $(BIN_DIR)/cthread.o $(BIN_DIR)/filas.o $(BIN_DIR)/tcb.o $(BIN_DIR)/support.o

escalonador.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/escalonador.c

cthread.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/cthread.c

filas.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/filas.c

tcb.o:
	$(CC) $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/tcb.c

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/*.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~


