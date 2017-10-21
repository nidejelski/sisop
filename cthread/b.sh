gcc -c teste/createejoin1.c -I"include"
gcc createejoin1.o bin/support.o bin/cthread.o bin/escalonador.o bin/filas.o bin/tcb.o -o createejoin1
