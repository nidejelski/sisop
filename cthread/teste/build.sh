gcc -c createejoin1.c
gcc createejoin1.o ../bin/support.o ../bin/cthread.o ../bin/escalonador.o ../bin/tcb.o -o teste1

#gcc -o teste createejoin1.c -L"../lib" -lcthread -Wall

