

/********************************************************************
	Vers. 17.2 - 11/09/2017
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "cdata.h"
#include "filas.h"

typedef struct fTcbs{
	int tid;
	int wait; // wait = -1 que ngm está esperando. Caso wait > 0 a thread id == wait está esperando pelo fim desta
} simpTcb;

typedef struct s_sem {
	int	count;	// indica se recurso está ocupado ou não (livre > 0, ocupado = 0)
	PFILA2	fila; 	// ponteiro para uma fila de threads bloqueadas no semáforo
} csem_t;


PFILA2 filaAptos;	
PFILA2 filaBloqs;
PFILA2 listaTcbs;


int filas_Init()
{
	listaTcbs = (PFILA2)malloc(sizeof(FILA2));
	filaAptos = (PFILA2)malloc(sizeof(FILA2));
	filaBloqs = (PFILA2)malloc(sizeof(FILA2));
	if(listaTcbs == NULL || filaAptos == NULL || filaBloqs == NULL)
		return -1;
	else
		return 0;
}

void filas_insereTcb(int tid){
	simpTcb *t;
	t->tid = tid;
	t->wait = -1;
	AppendFila2(listaTcbs, (void *)t);
}




// retorna 0 caso sucesso, != 0 c.c.
int filas_deletaTcb(int tid){
	simpTcb* it;
	if(FirstFila2(listaTcbs) == 0)
	{
		do
		{
			it = (simpTcb*)GetAtIteratorFila2(listaTcbs);
			if(it->tid == tid){
				DeleteAtIteratorFila2(listaTcbs);
				return 0;
			}	
		}
		while(NextFila2(listaTcbs)==0);
		return -1;
	}
	return -1;
}

int filas_setThreadWaiting(int tid, int wait) 
{	
	simpTcb* it;
	if(FirstFila2(listaTcbs) == 0)
	{
		do
		{
			it = (simpTcb*)GetAtIteratorFila2(listaTcbs);
			if(it->tid == tid){
				DeleteAtIteratorFila2(listaTcbs);
				it->wait = wait;
				AppendFila2(listaTcbs, it);
				return 0;
			}	
		}
		while(NextFila2(listaTcbs)==0);
		return -1;
	}
	return -1;
}

int filas_isThreadWaitingFor(int tid)
{
	simpTcb* it;
	if(FirstFila2(listaTcbs) == 0)
	{
		do
		{
			it = (simpTcb*)GetAtIteratorFila2(listaTcbs);
			if(it->wait == tid){
				return it->tid;
			}	
		}
		while(NextFila2(listaTcbs)==0);
		return -1;
	}
	return -1;
}

int filas_BloqsToAptos(int tid)
{
	TCB_t* it;
	if(FirstFila2(filaBloqs) == 0)
	{
		do
		{	
			it = GetAtIteratorFila2(filaBloqs);
			if(it->tid == tid){
				DeleteAtIteratorFila2(filaBloqs);
				return filas_insereAptos(it);
			}
		}
		while(NextFila2(filaBloqs) == 0);
	}
	return -1;
}

/*--------------------------------------------------------------------
Função: Insere um nodo na lista indicada, segundo o campo "prio" do TCB_t
	A fila deve estar ordenada (ou ter sido construída usado apenas essa funcao)
	O primeiro elemento da lista (first) é aquele com menor vamor de "prio"
Entra:	pfila -> objeto FILA2
	pnodo -> objeto a ser colocado na FILA2
Ret:	==0, se conseguiu
	!=0, caso contrário (erro)
--------------------------------------------------------------------*/
int	filas_InsertByPrio(PFILA2 pfila, TCB_t *tcb) {
	TCB_t *tcb_it;
	
	// pfile vazia?
	if (FirstFila2(pfila)==0) {
		do {
			tcb_it = (TCB_t *) GetAtIteratorFila2(pfila);
			if (tcb->prio < tcb_it->prio) {
				return InsertBeforeIteratorFila2(pfila, tcb);
			}
		} while (NextFila2(pfila)==0);
	}	
	return AppendFila2(pfila, (void *)tcb);
}


/*-------------------------------------------------------------------
Função:	Insere thread na fila de aptos do escalonador
Ret:	==0, se conseguiu
	    !=0, caso contrário
-------------------------------------------------------------------*/
int filas_insereAptos(TCB_t* thread){

    return filas_InsertByPrio(filaAptos, thread);

}



int filas_aptosVazia()
{
	return FirstFila2(filaAptos);
}


int filas_tam()
{
	int cont = 0;
	TCB_t *tcb_it;

	// pfile vazia?
	if (FirstFila2(listaTcbs)==0) {
		do {
			tcb_it = GetAtIteratorFila2(listaTcbs);
			cont++;
		} while (NextFila2(listaTcbs)==0);
	}

	return cont;
}


/*-------------------------------------------------------------------
Função:	Insere thread na fila de bloqueados do escalonador
Ret:	==0, se conseguiu
	!=0, caso contrário
-------------------------------------------------------------------*/

int filas_insereBloqs(TCB_t* thread){

    /// como não precisa se preocupar com a ordem na fila de bloqueados só insere no fim 
    return AppendFila2(filaBloqs, (void *)thread);
}



TCB_t* filas_popFila(PFILA2 fila)
{
	// fila vazia?
	if(FirstFila2(fila) == 0)
	{
		TCB_t* first = (TCB_t*)GetAtIteratorFila2(fila);
		if(DeleteAtIteratorFila2(fila) != 0){
			printf("Erro removendo\n");
		}
		return first;
	}
	else{
		//printf("fila vazia");
		return NULL;
	}
}


TCB_t* filas_popAptos()
{
	return filas_popFila(filaAptos);
}


TCB_t* filas_popBloqs()
{
	return filas_popFila(filaAptos);
}

int filas_removeBloqs(int tid)
{
	TCB_t* it;
	if(FirstFila2(filaBloqs) == 0)
	{
		do
		{	
			it = GetAtIteratorFila2(filaBloqs);
			if(it->tid == tid)
				return DeleteAtIteratorFila2(filaBloqs);
		}
		while(NextFila2(filaBloqs) == 0);
	}
	return -1;
}


void filas_printTidsFilas() {
	TCB_t *tcb_it;
	
	printf("\nFila de aptos:");
	// pfile vazia?
	if (FirstFila2(filaAptos)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaAptos);
			printf("(id:%d, prio:%u) -> ", tcb_it->tid, tcb_it->prio);
		} while (NextFila2(filaAptos)==0);
	}	
	printf("NULL\n");
	printf("Fila de bloqueados:");
	// pfile vazia?
	if (FirstFila2(filaBloqs)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaBloqs);
			printf("(id:%d, prio:%u) -> ", tcb_it->tid, tcb_it->prio);
		} while (NextFila2(filaBloqs)==0);
	}	
	printf("NULL\n");
	printf("Fila geral:");
	if(FirstFila2(listaTcbs) == 0){
		simpTcb* it;// = GetAtIteratorFila2(listaTcbs);
		do{
			it = GetAtIteratorFila2(listaTcbs);
			printf("(%d, %d) -> ", it->tid, it->wait);
		}
		while(NextFila2(listaTcbs) == 0);
	}
	printf("NULL\n\n");
}



TCB_t* filas_buscaEmFila(int tid, PFILA2 fila){
	TCB_t* it;
	if(FirstFila2(fila) == 0)
	{
		do
		{	
			it = GetAtIteratorFila2(fila);
			if(it->tid == tid)
				return it;
		}
		while(NextFila2(fila) == 0);
	}
	return NULL;

}

/*pesquisa uma tid na lista geral de tids
retorna a 1 caso encontre ou 0 c.c.*/
TCB_t* filas_existeThread(int tid){ 
    TCB_t *busca = filas_buscaEmFila(tid, filaAptos);
    if (busca != NULL && busca->tid == tid){
        return(busca);
    }
    busca = filas_buscaEmFila(tid, filaBloqs);
    if (busca != NULL && busca->tid == tid){
        return(busca);
    }
    return(NULL); //retorna null quando nao encontra nenhuma thread
}

