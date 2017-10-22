gcc -c -g teste/testecjoin.c
gcc testecjoin.o bin/support.o bin/cthread.o bin/escalonador.o bin/filas.o bin/tcb.o -o testecjoin
