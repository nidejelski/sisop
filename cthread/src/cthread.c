#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "support.h"
#include "cdata.h"
#include "cthread.h"

#define TAMANHO_PILHA 16384
#define MAXIMO_THREAD 100

int threadID = 0;

/*--------------------------------------------------------------------
Função: CCREATE
Parâmetros:
start: ponteiro para a função que a thread executará.
arg: um parâmetro que pode ser passado para a thread na sua criação. (Obs.: é um único parâmetro. Se for necessário
passar mais de um valor deve-se empregar um ponteiro para uma struct)
Retorno:
Quando executada corretamente: retorna um valor positivo, que representa o identificador da thread criada
Caso contrário, retorna um valor negativo.
--------------------------------------------------------------------*/

int ccreate(void* (*start)(void*), void *arg, int prio){

    ucontext_t G, *cp = &G;

	ucontext_t *contextoNovo = malloc(sizeof(ucontext_t));

	TCB_t* t = (TCB_t*) malloc(sizeof(TCB_t));
	contextoNovo->uc_stack.ss_sp = (char*)malloc(TAMANHO_PILHA);
	contextoNovo->uc_stack.ss_size = TAMANHO_PILHA;

	//No fim da função tem que retornar pro escalonador
	contextoNovo->uc_link = NULL;//[CONTEXTO ESCALONADOR]; //algo do tipo: escalonador->contexto_escalonador
	getcontext(contextoNovo);
	makecontext(contextoNovo,(void(*)(void))start,1,arg);

	//Seta parametros da TCB
	threadID++;
	t->tid = threadID;
	t->state = PROCST_CRIACAO;
	t->prio = prio;

    cp = contextoNovo;
	//G = contextoNovo;
	t->context = G;

    printf ("\nTID: %d \n", t->tid);


    //teste Insere APTOS
    if (threadID == 1){
        if (insereAptos(arg, t) == 0) printf ("\nSUCESSO APTOS\n");
        else printf("\nFALHA APTOS\n");
    }

    //teste Insere BLOQS
    else if (threadID == 2){
        if (insereBloqs(arg, t) == 0) printf ("\nSUCESSO BLOQS\n");
        else printf("\nFALHA BLOQS\n");
    }


     return t->tid;

        //Conferência de maximo de threads (100)
	//Algo do tipo: ( (escalonador->fila_aptos->size + escalonador->fila_bloqueados->size ) < MAXIMO_THREAD ))
   //     if( ([NR. THREADS NA FILA DE APTOS] + [NR. THREADS NA FILA DE BLOQUEADOS]) < MAXIMO_THREAD){
                  //Insere na fila de APTOS
                  //insereAptos(escalonador, t);
    //              return t->tid;
	//}
	//else{
		  //Erro
	//	  printf("Excedido o numero maximo de threads - THREAD: %d não foi criada\n",t->tid);
//	  free(contextoNovo);
//		  free(t);
//		  return -1;
//	}
}
