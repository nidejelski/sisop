#ifndef __filas__
#define __filas__

//#include "support.h"
#include "cdata.h"
//#include "tcb.h"


/*
	Retorna == 0 caso sucesso
	retorna != caso não;
*/
int filasInit();

/*
	Insere ordenado pelo Tid nas filas. 
	Retorna  == 0 caso conseguiu
			 != 0 caso não consiga
*/
int filas_insereAptos(TCB_t* thread);
int filas_insereBloqs(TCB_t *thread);


/*
	Retorna o primeiro elemento da fila, REMOVENDO-O dela. 
	Retorna NULL em caso de erro.
*/
TCB_t* filas_popAptos();
TCB_t* filas_popBloqs();


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