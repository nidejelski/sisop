#include <stdio.h>
#include <stdlib.h>
#include "cthread.h"
//#include "cthread.c"
#include "support.h"
#include "escalonador.h"
//#include "escalonador.c"

//testes
void f1(){
    printf ("\nFUNCAO 1 \n");
    //printf ("PRECISA VOLTAR PRA MAIN!\n");
    ccyield();
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
    //escalonadorInit(); // Esta função só deve ser usada fora das funções da lib para testes

    //inicia a THREAD MAIN
    escalonadorInit();
    ucontext_t contextoEscalona;
    contextoEscalona.uc_stack.ss_sp = (char*)malloc(TAMANHO_PILHA);
    contextoEscalona.uc_stack.ss_size = TAMANHO_PILHA;
    getcontext(&contextoEscalona);

    if (escalonator->threadEmExec == NULL){
        TCB_t* threadMain = malloc(sizeof(TCB_t));
        threadID++;
        threadMain->tid = threadID;
        threadMain->state = PROCST_CRIACAO;
        threadMain->prio = 0;
        threadMain->context = contextoEscalona;
        insereAptos(threadMain);
        escalonator->threadEmExec = threadMain;
        escalonadorExec();
    }

    printf ("\n Iniciou escalonador e colocou a main como primeiro thread! \n");


    if (NextFila2(getFilaAptos()) == -1) printf ("Lista de Aptos Vazia! \n");

    //Testa qual thread está em execução
    TCB_t* teste = getThreadEmExec();
    if (teste == NULL)
        printf ("\n THREAD EM EXECUCAO: NULL \n");
    else if (teste->tid == 1)
        printf ("\n THREAD EM EXECUCAO: MAIN \n");
    else
        printf ("\n THREAD EM EXECUCAO: %d \n", teste->tid);

    //if (escalona->filaAptos == NULL) {
    //    printf("LISTA DE APTOS ESTA VAZIA\n");
   // }
   // if (escalona->filaBloqs == NULL) {
   //     printf("LISTA DE BLOQS ESTA VAZIA\n");
    //}

    //testes threads
    //cria Thread 1
    int t1 = ccreate((void*)f1,NULL,0);

    if (t1 == 0) printf ("\n Nao conseguiu criar thread ");
    else printf ("\n Thread %d criada!", t1);

    //cria Thread2
    int t2 = ccreate((void*)f2,NULL,1);

    if (t2 == 0) printf ("\n Nao conseguiu criar thread ");
    else printf ("\n Thread %d criada!", t2);


    int tamAptos = pegaTamFila(escalonator->filaAptos);

    printf ("\n TAMANHO DA FILA DE APTOS: %d \n", tamAptos);

    //if (t2 == 0) printf ("\n Nao conseguiu criar thread 2l");
    //else printf ("\n Thread %d criada!", t2);

    //testa se fila de APTOS está vazia após inserção
    //printf ("\n FILA APTOS ESTA VAZIA? \n");
    if (FirstFila2(getFilaAptos()) == 0) printf ("\n SELECIONADO PRIMEIRO ELEMENTO EM APTOS! \n");
    TCB_t* thread_TESTE = GetAtIteratorFila2(getFilaAptos());

    printf ("\nAtributos da Thread: \n");
    printf ("TID: %d \n", thread_TESTE->tid);
    printf ("ESTADO: %d \n", thread_TESTE->state);
    printf ("PRIORIDADE: %d \n", thread_TESTE->prio);


    //testa se fila de BLOQS está vazia após inserção
  //  printf ("\n FILA BLOQS ESTA VAZIA? \n");
  //  if (FirstFila2(getFilaBloqs()) == 0) printf ("\n SELECIONADO PRIMEIRO ELEMENTO EM BLOQS! \n");
  //  TCB_t* thread_TESTE2 = GetAtIteratorFila2(getFilaBloqs());

 //   printf ("\nAtributos da Thread %d: \n", t2);
 //   printf ("TID: %d \n", thread_TESTE2->tid);
 //   printf ("ESTADO: %d \n", thread_TESTE2->state);
 //   printf ("PRIORIDADE: %d \n", thread_TESTE2->prio);


    //teste de EXECUCAO DA THREAD -- primeira que estiver em aptos
    escalonadorExec();


    //teste Remove APTOS
    //if (removeAptos(escalona) == 0) printf ("   SUCESSO REMOVE APTOS \n");

    //teste Remove BLOQS
//    if (removeBloqs() == 0) printf ("   SUCESSO REMOVE BLOQS \n");


  //  if (NextFila2(getFilaAptos()) == -1) printf ("\n Lista de Aptos Vazia! \n");
    //FirstFila2(escalona->filaAptos);
    //if (NextFila2(escalona->filaAptos) == -3 ) printf ("\n FIM DA FILA! \n");

    return 0;
}
