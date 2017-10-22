#ifndef __filas__
#define __filas__

//#include "support.h"
#include "cdata.h"
//#include "tcb.h"


/*
	Retorna == 0 caso sucesso
	retorna != caso não;
*/
int filas_Init();


void filas_insereTcb(int tid);
int filas_deletaTcb(int tid);
int filas_setThreadWaiting(int tid, int wait);
int filas_isThreadWaitingFor(int tid);

int filas_BloqsToAptos(int tid);


/*
	Insere ordenado pelo Tid nas filas. 
	Retorna  == 0 caso conseguiu
			 != 0 caso não consiga
*/
int filas_insereAptos(TCB_t* thread);
int filas_insereBloqs(TCB_t *thread);


/*
	retorna 1 caso a fila esteja vazia, 0 c.c.
*/
int filas_aptosVazia();

/*
	Retorna o primeiro elemento da fila, REMOVENDO-O dela. 
	Retorna NULL em caso de erro.
*/
TCB_t* filas_popAptos();
TCB_t* filas_popBloqs();

/*
	retorna 0 caso sucesso, != 0 c.c.
*/
int filas_removeBloqs(int tid);


/*
	retorna a soma do tamanho das 2 filas
*/
int filas_tam();


// printa os Tids dos elementos da fila. Usado para debug
void filas_printTidsFilas();


/*
	retorna o TCB caso ele exista, ou NULL c.c.
*/
TCB_t* filas_existeThread(int tid);



// uso interno em filas.c apenas
//int	filas_InsertByPrio(PFILA2 pfila, TCB_t *tcb);


// fora de uso por enquanto
//int filas_removeAptos();
//int filas_removeBloqs();

#endif