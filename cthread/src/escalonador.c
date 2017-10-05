#include <stdlib.h>
#include <ucontext.h>
#include "escalonador.h"
#include "support.h"
#include "cdata.h"

Escalonador* escalonador;

Escalonador* escalonadorInit(){
	//instancia escalonador
        Escalonador* escalonator = (Escalonador*) malloc(sizeof(Escalonador));
	
        //cria as filas
        escalonator->filaAptos = CreateFila2(); //uso da biblioteca de filas
	escalonator->filaBloqs = CreateFila2();	
	escalonator->threadEmExec = NULL;

	//inicia contexto
	ucontext_t* contextoEscalonator = (ucontext_t*) malloc(sizeof(ucontext_t));
	escalonator->contextoEscalonador = contextoEscalonator;	
	
	return escalonator;
}

int insereAptos(Escalonador* escalonator, s_TCB *thread){
	AppendFila2(escalonator->filaAptos, thread); 
	return 1;
}

s_TCB* retiraAptos(Escalonador* escalonator){
}

int insereBloqs(Escalonador* escalonator, s_TCB *thread){
	appendFila2(escalonator->filaBloqs, thread); 
	return 1;
}

s_TCB* retiraBloqs(Escalonador* escalonator){
}

void liberaEscalonador(int id){
	//free()
}

void escalonadorExec(){
	/*Define contexto do escalonador. Se thread acabar, vem para esse contexto*/	
	getcontext(escalonador->contextoEscalonador); 
	
	if(escalonador->threadEmExec->estado != MAIN){	
		liberaEscalonador(escalonador->threadEmExec->tid);
		free(escalonador->threadEmExec);
	}
	trocaContexto();
	
}

void trocaContexto(){
	//#define	NXTFILA_VAZIA		1
        //#define	NXTFILA_ITERINVAL	2
        //#define	NXTFILA_ENDQUEUE	3
        //int NextFila2(PFILA2 pFila);
	
	if(NextFila2(escalonador->filaAptos) != 1 ){
		escalonador->threadEmExec = retiraAptos(escalonador);
		setcontext(escalonador->threadEmExec->contexto); // executa thread
	}
}

