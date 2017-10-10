#include <stdio.h>
#include <stdlib.h>
#include "cthread.h"
#include "cthread.c"
#include "support.h"
#include "escalonador.h"
#include "escalonador.c"

//testes
void f1(){
    printf ("\nFUNCAO 1 \n");
}

void f2(){
    printf ("\nFUNCAO 2 \n");
}


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

    if (NextFila2(escalona->filaAptos) == -1) printf ("\n Lista de Aptos Vazia! \n");
    //if (escalona->filaAptos == NULL) {
    //    printf("LISTA DE APTOS ESTA VAZIA\n");
   // }
   // if (escalona->filaBloqs == NULL) {
   //     printf("LISTA DE BLOQS ESTA VAZIA\n");
    //}

    //testes threads
    //cria Thread 1
    int t1 = ccreate((void*)f1,escalona,0);

    if (t1 == 0) printf ("\n Nao conseguiu criar thread 1");
    else printf ("\n Thread %d criada!", t1);

    //cria Thread2
    int t2 = ccreate((void*)f2,escalona,0);

    if (t2 == 0) printf ("\n Nao conseguiu criar thread 1");
    else printf ("\n Thread %d criada!", t2);

    //FirstFila2(escalona->filaAptos);
    //if (NextFila2(escalona->filaAptos) == -3 ) printf ("\n FIM DA FILA! \n");

    return 0;
}
