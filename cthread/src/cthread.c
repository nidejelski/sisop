#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "support.h"
#include "cdata.h"
#include "cthread.h"
#include "escalonador.h"

#define TAMANHO_PILHA 16384
#define MAXIMO_THREAD 100

int threadID = 0;

extern Escalonador* escalonator;

int pegaTamFila(PFILA2 fila){
    int i=1;

    if (FirstFila2(fila) == 0){
        while(NextFila2(fila) == 0) {
            i++;
        }
    }
    else return 0;

    FirstFila2(fila);
    return i;
}

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

	if(!getIniciado())
		escalonadorInit();

    ucontext_t contextoNovo;

	TCB_t* t = (TCB_t*) malloc(sizeof(TCB_t));
	contextoNovo.uc_stack.ss_sp = (char*)malloc(TAMANHO_PILHA);
	contextoNovo.uc_stack.ss_size = TAMANHO_PILHA;

	//No fim da função tem que retornar pro escalonador
	contextoNovo.uc_link = escalonator->contexto_escalonador;//[CONTEXTO ESCALONADOR]; //algo do tipo: escalonador->contexto_escalonador
	getcontext(&contextoNovo);
	makecontext(&contextoNovo,(void(*)(void))start,1,arg);

	//Seta parametros da TCB
	threadID++;
	t->tid = threadID;
	t->state = PROCST_CRIACAO;
	t->prio = prio;

	//G = contextoNovo;
	t->context = contextoNovo;

    printf ("\nTID: %d \n", t->tid);


    int tamAptos,tamBloqs;

    tamAptos = pegaTamFila(escalonator->filaAptos);
    tamBloqs = pegaTamFila(escalonator->filaBloqs);

    //Garante o maximo de threads
    if (tamAptos + tamBloqs < MAXIMO_THREAD){
        if (insereAptos(t) == 0) printf ("\nSUCESSO INSERE APTOS\n");
        return t->tid;
    }
    else {
        printf("ATINGIU MAXIMO DE THREADS!");
        //free(t->context)
        free(t);
        //free(contextoNovo);
        return -1;
    }

    //teste Insere APTOS
    //if (threadID == 2){
    //    if (insereAptos(t) == 0) printf ("\nSUCESSO INSERE APTOS\n");
    //    else printf("\nFALHA APTOS\n");
    //}

    //teste Insere BLOQS
    //else if (threadID == 3){
    //    if (insereBloqs(t) == 0) printf ("\nSUCESSO INSERE BLOQS\n");
    //    else printf("\nFALHA BLOQS\n");
    //}

	//return t->tid;
}


void ccyield(void)
{
    //Comentado por Daniel em 18/10 - Erro floating point exception
	//if(!getIniciado())
	//	escalonadorInit();

    printf ("\n ENTROU EM CCYIELD \n ");

	//provavelmente neste ponto teremos que acrescentar o tepmo de execução atual da thread no campo prioridade

	if(insereAptos(escalonator->threadEmExec) == 0)
		printf("Thread atual inserida em aptos\n");
	else
		printf("Falha ao inserir\n");

	escalonadorExec();

	/*
	if(setContext(atual.context) != -1)
		printf("contexto atualizado\n");
	else
		printf("Erro\n");
	*/
}

/*
int sched_dispatch(int reschedulecurrent){
	FIFO_t *currentfifo = sched_choose_FIFO();
	if (currentfifo == NULL)
		return -1;
	TCB_t *prevtcb = currenttcb;
	TCB_t *nexttcb = sched_get_next_thread(currentfifo);1
	if (nexttcb == NULL)
		return -1;
	if (reschedulecurrent)
		sched_add_thread(currenttcb);
	currenttcb = nexttcb;
	tcb_setstate(currenttcb,MTHREAD_STATE_RUNNING);
	int result = tcb_swapcontext(prevtcb,currenttcb);
	return result;
}
*/
