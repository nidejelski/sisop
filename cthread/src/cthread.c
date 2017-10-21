#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "support.h"
#include "cdata.h"
#include "cthread.h"
#include "escalonador.h"
#include "tcb.h"

#define TAMANHO_PILHA 16384
#define MAXIMO_THREAD 100

int threadID = 0;
int debugPrints = 1;
int maintcb = 0;

/*
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
*/


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
	if(debugPrints)
		printf("Entrando em ccreate... ");

	if(!esca_getIniciado())
		esca_escalonadorInit();

	if(!maintcb){
		if(debugPrints)
			printf("Criando thread de main\n");
		maintcb = 1;
		TCB_t* main = tcb_createTCB(0);
		getcontext(&main->context);
		esca_setThreademExec(main);

		/// adiciona na lista de threads existentes <<<<<<<<<<<<<<<<<<<<<<<<<<<< caso precise isso algum dia
	}

	TCB_t* t = tcb_createTCB(++threadID);
	tcb_createContext(t ,&esca_execThread, start, arg, TAMANHO_PILHA);

	if(debugPrints)
    	printf ("\nTID: %d \n", t->tid);

    int tamAptos,tamBloqs;

    tamAptos = 0;//pegaTamFila(escalonator->filaAptos);
    tamBloqs = 0;//pegaTamFila(escalonator->filaBloqs);

    //Garante o maximo de threads
    if (tamAptos + tamBloqs < MAXIMO_THREAD){
        if (filas_insereAptos(t) == 0) 
        	if(debugPrints) 
        		printf ("\nSUCESSO INSERE APTOS\n");
        return t->tid;
    }
    else {
    	if(debugPrints)
        	printf("ATINGIU MAXIMO DE THREADS!");
        //free(t->context)   <<<<<<<<<<<<<<<<<<<<<<<<<<< ver depois
        free(t);
        //free(contextoNovo);
        return -1;
    }

}


int cyield(void)
{
	//if(!getIniciado())
	//	escalonadorInit();

	if(debugPrints)
    	printf ("\n ENTROU EM CCYIELD \n ");

	//provavelmente neste ponto teremos que acrescentar o tepmo de execução atual da thread no campo prioridade  <<<<<<<<<<<<<


	if(maintcb != 0 && filas_insereAptos(esca_getThreadEmExec()) == 0)
		if(debugPrints)
			printf("Thread atual inserida em aptos\n");
	else
		if(debugPrints)
			printf("Falha ao inserir\n");

	esca_dispatcher();

	return 0;
}


int cjoin (int tid){	
	esca_escalonadorInit();

	TCB_t *thread = filas_existeThread(tid); //thread solicitada para cjoin  <<<<<<<<<<<<<<<<<<<<<<<<<<<< tá tendo um warning aqui, ver depois
	TCB_t *threadExec = NULL;//threadEmExecucao(); //thread que chamou cjoin MUDAR NOME DA FUNÇÃO <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< comentei aqui só pra compilar
	/// depois se der troca o nome dessa variável, pq pode confundir com a que tem em escalonador.c

	if (thread == NULL){	//se a thread nao existe
		printf("ERRO: Thread %d nao existe\n",tid);
		return (-1);
	}
	//testa se essa thread é esperada por alguma outra thread
	if (thread->espera == 0){	//é zero quando nenhuma outra fez cjoin para essa thr
			getcontext(&(threadExec->context)); //verificar essa linha!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			thread->aguardada_por = threadExec->tid;	//a que está em exec espera pela thr que está sendo setada no campo espera
			threadExec->aguarda_termino = tid;	//era nossa exec que aguarda o fim da thr->tid
			threadExec->state = PROCST_BLOQ;
			//manda thr em exec para fila de bloq
			//encerra função em exec
			//chama escalonador
		}
	else{
		printf("ERRO: impossivel realizar cjoin para a thread %d \n", tid );
		return(-1);
	}
	
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
