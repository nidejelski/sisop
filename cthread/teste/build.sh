gcc -c createejoin1.c
gcc createejoin1.o ../bin/support.o ../bin/cthread.o ../bin/escalonador.o ../bin/filas.o ../bin/tcb.o -o createejoin1

#gcc -o teste createejoin1.c -L"../lib" -lcthread -Wall

