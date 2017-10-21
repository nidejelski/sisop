#include <stdio.h>
#include <stdlib.h>
#include "../include/filas.h"
#include "../include/cdata.h"
//#include "../include/support.h"
//#include "../include/escalonador.h"


int main()
{
	filas_Init();

	TCB_t* tcb1, *tcb2, *tcb3, *tcb4, *tcb5;
	tcb1 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb1->tid = 1;
	tcb1->prio = 1;
	tcb2 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb2->tid = 2;
	tcb2->prio = 2;
	tcb3 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb3->tid = 3;
	tcb3->prio = 3;
	tcb4 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb4->tid = 4;
	tcb4->prio = 4;
	tcb5 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb5->tid = 5;
	tcb5->prio = 5;

	TCB_t* t ;

	filas_printTidsFilas();

	filas_insereAptos(tcb2);
	filas_insereAptos(tcb4);
	filas_insereAptos(tcb1);

	filas_printTidsFilas();

	t = filas_popAptos();
	printf("t = %d\n", t->tid);
	filas_insereAptos(tcb3);
	filas_insereAptos(tcb5);

	filas_printTidsFilas();


	t = filas_popAptos();
	printf("t = %d\n", t->tid);
	
	t = filas_popAptos();
	printf("t = %d\n", t->tid);
	t = filas_popAptos();

	filas_insereBloqs(tcb1);
	filas_insereBloqs(tcb2);
	filas_insereBloqs(tcb3);
	filas_insereBloqs(tcb4);

	filas_printTidsFilas();

	t =filas_existeThread(1);
	if(t == NULL)
		printf("t == NULL\n");
	else
		printf("t = %d\n", t->tid);

	t =filas_existeThread(2);
	if(t == NULL)
		printf("t == NULL\n");
	else
		printf("t = %d\n", t->tid);

	t =filas_existeThread(3);
	if(t == NULL)
		printf("t == NULL\n");
	else
		printf("t = %d\n", t->tid);

	t =filas_existeThread(4);
	if(t == NULL)
		printf("t == NULL\n");
	else
		printf("t = %d\n", t->tid);

	t =filas_existeThread(5);
	if(t == NULL)
		printf("t == NULL\n");
	else
		printf("t = %d\n", t->tid);

	t =filas_existeThread(6);
	if(t == NULL)
		printf("t == NULL\n");
	else
		printf("t = %d\n", t->tid);

	printf("Tamanho das filas = %d\n", filas_tam());


	if(filas_aptosVazia())
		printf("Fila de aptos vazia\n");
	else	
		printf("Fila de aptos tem algo\n");

	filas_popAptos();

	if(filas_aptosVazia())
		printf("Fila de aptos vazia\n");
	else	
		printf("Fila de aptos tem algo\n");

	filas_printTidsFilas();

	printf("Tamanho das filas = %d\n", filas_tam());	




	return 0;
}