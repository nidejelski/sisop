gcc -c -g teste/createejoin2.c
gcc createejoin2.o bin/support.o bin/cthread.o bin/escalonador.o bin/filas.o bin/tcb.o -o createejoin2
