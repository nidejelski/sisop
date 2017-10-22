gcc -c -g teste/csem.c
gcc csem.o bin/support.o bin/cthread.o bin/escalonador.o bin/filas.o bin/tcb.o -o csem
