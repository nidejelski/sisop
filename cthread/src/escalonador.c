#include <stdlib.h>
#include <ucontext.h>
#include "support.h"
#include "cdata.h"

Escalonador* escalonator;

Escalonador* escalonadorInit(){
	//instancia escalonador
    escalonator = (Escalonador*) malloc(sizeof(Escalonador));

    //cria as filas
    PFILA2 filaAP = malloc(sizeof(PFILA2));
    PFILA2 filaBL = malloc(sizeof(PFILA2));

    if (CreateFila2(filaAP) == 0) escalonator->filaAptos = NULL;
	if (CreateFila2(filaBL) == 0) escalonator->filaBloqs = NULL;
	//escalonator->threadEmExec = NULL;

	//inicia contexto
	ucontext_t* contextoEscalonator = (ucontext_t*) malloc(sizeof(ucontext_t));
	escalonator->contexto_escalonador = contextoEscalonator;

    printf ("Iniciou escalonador! \n");

	return escalonator;
}

int insereAptos(Escalonador* escalonator, TCB_t *thread){
	//AppendFila2(escalonator->filaAptos, thread);
	return 1;
}

TCB_t* retiraAptos(Escalonador* escalonator){
    printf ("retirei de APTOS \n");
}

int insereBloqs(Escalonador* escalonator, TCB_t *thread){
	//appendFila2(escalonator->filaBloqs, thread);
	return 1;
}

TCB_t* retiraBloqs(Escalonador* escalonator){
    printf ("retirei de BLOQ \n");
}

void liberaEscalonador(int id){
	//free()
	printf ("liberei escalonador \n");
}

void escalonadorExec(){
	/*Define contexto do escalonador. Se thread acabar, vem para esse contexto*/
	getcontext(escalonator->contexto_escalonador);

	if(escalonator->threadEmExec->tid != 0){ // 0 == MAIN
		liberaEscalonador(escalonator->threadEmExec->tid);
		free(escalonator->threadEmExec);
	}
	trocaContexto();

}

void trocaContexto(){
	if(NextFila2(escalonator->filaAptos) != -1) {  //se fila não for vazia
		printf ("TROCA CONTEXTO");
		//escalonator->threadEmExec = retiraAptos(escalonator);
		//setcontext(escalonator->threadEmExec->contexto); // executa thread
	}
}

