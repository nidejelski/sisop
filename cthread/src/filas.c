

/********************************************************************
	Vers. 17.2 - 11/09/2017
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "cdata.h"
#include "filas.h"

PFILA2 filaAptos;	
PFILA2 filaBloqs;

int filas_Init()
{
	filaAptos = (PFILA2)malloc(sizeof(PFILA2));
	filaBloqs = (PFILA2)malloc(sizeof(PFILA2));
	if(filaAptos == NULL || filaBloqs == NULL)
		return -1;
	else
		return 0;
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
	if (FirstFila2(filaAptos)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaAptos);
			cont++;
		} while (NextFila2(filaAptos)==0);
	}	
	// pfile vazia?
	if (FirstFila2(filaBloqs)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaBloqs);
			cont++;
		} while (NextFila2(filaBloqs)==0);
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
	
	printf("Fila de aptos:");
	// pfile vazia?
	if (FirstFila2(filaAptos)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaAptos);
			printf("%d -> ", tcb_it->tid);
		} while (NextFila2(filaAptos)==0);
	}	
	printf("NULL\n");
	printf("Fila de bloqueados:");
	// pfile vazia?
	if (FirstFila2(filaBloqs)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaBloqs);
			printf("%d -> ", tcb_it->tid);
		} while (NextFila2(filaBloqs)==0);
	}	
	printf("NULL\n\n");
}



/*Busca uma trhead em uma fila*/
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

/*pesquisa uma tid nas filas de aptos e de bloqueados
retorna a thred encontrada em qualquer uma das filas, ou NULL em caso de nao encontrar*/

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




/*-------------------------------------------------------------------
Função:	Remove thread na fila de aptos do escalonador
Ret:	==0, se conseguiu
	    >0, caso contrário
-------------------------------------------------------------------*/

/*
int filas_removeAptos(){
    int fAux = FirstFila2(escalonator->filaAptos);
    if (fAux == 0){
        if(DeleteAtIteratorFila2(escalonator->filaAptos) == 0){
            printf ("\n retirei de APTOS \n");
            return 0;
        }
        else {
            printf ("fila vazia ou itinval\n");
            return 1;
        }
    }
    else{
        printf("fila vazia ou erro | erro : %d", fAux);
        return 2;
    }
}
*/

/*-------------------------------------------------------------------
Função:	Remove thread na fila de bloqueados do escalonador
Ret:	==0, se conseguiu
	    >0, caso contrário
-------------------------------------------------------------------*/

/*
int filas_removeBloqs(){
    int fAux = FirstFila2(escalonator->filaBloqs);
    if (fAux == 0){
        if(DeleteAtIteratorFila2(escalonator->filaBloqs) == 0){
            printf ("\n retirei de BLOQS \n");
            return 0;
        }
        else {
            printf ("fila vazia ou itinval\n");
            return 1;
        }
    }
    else{
        printf("fila vazia ou erro | erro : %d", fAux);
        return 2;
    }
}

*/