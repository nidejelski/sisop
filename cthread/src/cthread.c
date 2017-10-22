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
int debugPrints = 0;
int maintcb = 0;
unsigned int lastTime = 0;


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
	if(0)
		printf("Entrando em ccreate... \n");

	if(!esca_getIniciado()){
		startTimer();
		esca_escalonadorInit();
	}

	if(!maintcb){
		if(0)
			printf("Criando thread de main\n");
		maintcb = 1;
		TCB_t* main = tcb_createTCB(0);
		getcontext(&main->context);
		esca_setThreademExec(main);

		/// adiciona na lista de threads existentes <<<<<<<<<<<<<<<<<<<<<<<<<<<< caso precise isso algum dia
	}

	TCB_t* t = tcb_createTCB(++threadID);
	tcb_createContext(t ,&esca_execThread, start, arg, TAMANHO_PILHA);

	if(0)
    	printf ("TID criado: %d \n", t->tid);

    int tamFilas = filas_tam();

    //Garante o maximo de threads
    if (tamFilas < MAXIMO_THREAD){
        if (filas_insereAptos(t) != 0) 
        	printf("Erro ao inserir\n");
        return t->tid;
    }
    else {
        printf("ATINGIU MAXIMO DE THREADS!");
        //free(t->context)   <<<<<<<<<<<<<<<<<<<<<<<<<<< ver depois
        free(t);
        //free(contextoNovo);
        return -1;
    }

}


int cyield(void)
{
	if(!esca_getIniciado()){
		startTimer();
		esca_escalonadorInit();
	}

	if(debugPrints)
    	printf ("ENTROU EM CCYIELD \n ");

	//provavelmente neste ponto teremos que acrescentar o tepmo de execução atual da thread no campo prioridade  <<<<<<<<<<<<<

    TCB_t* t = esca_getThreadEmExec();
    t->prio += stopTimer();
    startTimer();

	if(maintcb != 0 && filas_insereAptos(t) != 0)
		printf("Falha ao inserir\n");

	if(esca_dispatcher() == -1){
		if(debugPrints)
			printf("Nao tinha outra thread em aptos, segue o baile\n");
		return -1;
	}

	return 0;
}


int cjoin (int tid){	
	esca_escalonadorInit();

	TCB_t *thread = (TCB_t*)filas_existeThread(tid); //thread solicitada para cjoin  <<<<<<<<<<<<<<<<<<<<<<<<<<<< tá tendo um warning aqui, ver depois
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


int csem_init (csem_t *sem, int count)
{

	sem->count = count;
	//int x = CreateFila2(sem->fila);
	sem->fila = (PFILA2)malloc(sizeof(FILA2));
	if(sem->fila == NULL){
		printf("fila == NULL\n");
		return -1;
	}
	return 0;
}


int cwait(csem_t *sem)
{
	if(sem->count > 0) /// há recurso disponível
	{
		sem->count--;
		return 0;
	}
	else /// não há recurso disponível
	{
		TCB_t* t = esca_getThreadEmExec();
		if(AppendFila2(sem->fila, (void*)t) != 0)
			return -1;
		esca_dispatcher();
		return 0;
	}
}

int csignal(csem_t *sem)
{
	sem->count++;
	if(FirstFila2(sem->fila) != 0)
		return -1;
	TCB_t* t= (TCB_t*)GetAtIteratorFila2(sem->fila);
	DeleteAtIteratorFila2(sem->fila);
	filas_insereAptos(t);
	return 0;

}