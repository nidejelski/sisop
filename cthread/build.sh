gcc -c main.c -I"include"
gcc main.o bin/support.o bin/escalonador.o bin/cthread.o -o main
