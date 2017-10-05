#include <stdio.h>
#include <stdlib.h>
#include "cthread.h"
#include "support.h"
#include "escalonador.h"
#include "escalonador.c"

int main(int argc, char *argv[])
{
    printf("Hello world!\n");

    //testes filas
    /*
    PFILA2 fila = malloc(sizeof(PFILA2));

    if (CreateFila2(fila) == 0){
        printf ("OMFG!!!\n");

        if(NextFila2(fila) == -1){ //lista vazia
            printf ("LISTA VAZIA!!!");
        }
    }
    */
    //teste Tempos
    /*
      startTimer();
      printf ("diferenca: %d", stopTimer());
    */


    //testes escalonador
    Escalonador* escalona;

    escalona = escalonadorInit();

    if (escalona->filaAptos == NULL) {
        printf("LISTA DE APTOS ESTA VAZIA\n");
    }
    if (escalona->filaBloqs == NULL) {
        printf("LISTA DE BLOQS ESTA VAZIA\n");
    }



    //testes threads

    return 0;
}
