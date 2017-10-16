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
    printf("INICIO DA MAIN!\n");

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

    if (NextFila2(escalona->filaAptos) == -1) printf ("Lista de Aptos Vazia! \n");

    //Testa qual thread está em execução
    if (escalona->threadEmExec == NULL) printf ("\n THREAD EM EXECUCAO: NULL \n", escalona->threadEmExec);
    else printf ("\n THREAD EM EXECUCAO: %d ", escalona->threadEmExec->tid);


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
    int t2 = ccreate((void*)f2,escalona,1);

    if (t2 == 0) printf ("\n Nao conseguiu criar thread 2l");
    else printf ("\n Thread %d criada!", t2);

    //testa se fila de APTOS está vazia após inserção
    printf ("\n FILA APTOS ESTA VAZIA? \n");
    if (FirstFila2(escalona->filaAptos) == 0) printf ("\n SELECIONADO PRIMEIRO ELEMENTO EM APTOS! \n");
    TCB_t* thread_TESTE = GetAtIteratorFila2(escalona->filaAptos);

    printf ("\nAtributos da Thread %d: \n", t1);
    printf ("TID: %d \n", thread_TESTE->tid);
    printf ("ESTADO: %d \n", thread_TESTE->state);
    printf ("PRIORIDADE: %d \n", thread_TESTE->prio);


    //testa se fila de BLOQS está vazia após inserção
    printf ("\n FILA BLOQS ESTA VAZIA? \n");
    if (FirstFila2(escalona->filaBloqs) == 0) printf ("\n SELECIONADO PRIMEIRO ELEMENTO EM BLOQS! \n");
    TCB_t* thread_TESTE2 = GetAtIteratorFila2(escalona->filaBloqs);

    printf ("\nAtributos da Thread %d: \n", t2);
    printf ("TID: %d \n", thread_TESTE2->tid);
    printf ("ESTADO: %d \n", thread_TESTE2->state);
    printf ("PRIORIDADE: %d \n", thread_TESTE2->prio);


    //teste de EXECUCAO DA THREAD
    escalonadorExec();

    //testa qual Thread esta em execucao no momento
    if (escalona->threadEmExec == NULL) printf ("\n THREAD EM EXECUCAO: NULL \n", escalona->threadEmExec);
    else printf ("\n THREAD EM EXECUCAO: %d ", escalona->threadEmExec->tid);


    //teste Remove APTOS
    //if (removeAptos(escalona) == 0) printf ("   SUCESSO REMOVE APTOS \n");

    //teste Remove BLOQS
    if (removeBloqs(escalona) == 0) printf ("   SUCESSO REMOVE BLOQS \n");


    if (NextFila2(escalona->filaAptos) == -1) printf ("\n Lista de Aptos Vazia! \n");
    //FirstFila2(escalona->filaAptos);
    //if (NextFila2(escalona->filaAptos) == -3 ) printf ("\n FIM DA FILA! \n");

    return 0;
}
