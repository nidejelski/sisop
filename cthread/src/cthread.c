#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "support.h"
#include "cdata.h"
#include "cthread.h"

#define TAMANHO_PILHA 16384
#define MAXIMO_THREAD 100

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
	
	ucontext_t* contextoNovo = (ucontext_t*) malloc(sizeof(ucontext_t));

	s_TCB* t = (s_TCB*) malloc(sizeof(s_TCB));
	contextoNovo->uc_stack.ss_sp = (char*)malloc(TAMANHO_PILHA);
	contextoNovo->uc_stack.ss_size = TAMANHO_PILHA;
		
	// No fim da função tem que retornar pro escalonador	
	contextoNovo->uc_link = [CONTEXTO ESCALONADOR]; //algo do tipo: escalonador->contexto_escalonador 
	getcontext(contextoNovo);
	makecontext(contextoNovo,(void(*)(void))start,1,arg); 
	
	// seta parametros da TCB
	t->tid = id++;
	t->state = PROCST_CRIACAO;
	t->prio = prio;
	t->context = contextoNovo;
  
        // Conferência de maximo de threads (100)
	//algo do tipo: ( (escalonador->fila_aptos->size + escalonador->fila_bloqueados->size ) < MAXIMO_THREAD ))
        if( ([NR. THREADS NA FILA DE APTOS] + [NR. THREADS NA FILA DE BLOQUEADOS]) < MAXIMO_THREAD){
                  //insere na fila de APTOS
                  //insereAptos(escalonador, t);
                  return t->tid;
	}
	else{
		  printf("Excedido o numero maximo de threads - THREAD: %d não foi criada\n",t->tid); 	
		  free(contextoNovo);
		  free(t);	
		  return 0;						 
	}
}
