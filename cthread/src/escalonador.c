#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "escalonador.h"
#include "support.h"
#include "cdata.h"

Escalonador* escalonator;

int escalonador_iniciado = 0;

TCB_t* maintct;

void escalonadorInit(){
	//instancia escalonador
    escalonator = (Escalonador*) malloc(sizeof(Escalonador));

    //cria as filas
    PFILA2 filaAP = malloc(sizeof(PFILA2));
    PFILA2 filaBL = malloc(sizeof(PFILA2));

    if (CreateFila2(filaAP) == 0) escalonator->filaAptos = filaAP;
	if (CreateFila2(filaBL) == 0) escalonator->filaBloqs = filaBL;
	escalonator->threadEmExec = NULL;

	//inicia contexto
	ucontext_t* contextoEscalonator = malloc(sizeof(ucontext_t));
	escalonator->contexto_escalonador = contextoEscalonator;

    printf ("Iniciou escalonador! \n");

    escalonador_iniciado = 1;
}

int getIniciado(){
    return escalonador_iniciado;
}

/*-------------------------------------------------------------------
Função:	Insere thread na fila de aptos do escalonador
Ret:	==0, se conseguiu
	    1, caso contrário
-------------------------------------------------------------------*/
int insereAptos(TCB_t* thread){
    if(AppendFila2(escalonator->filaAptos, thread) == 0) {
       printf("Inseriu na fila de Aptos\n");
       return 0;
    }
    else printf("Oops!");
    return 1;

}

/*-------------------------------------------------------------------
Função:	Remove thread na fila de aptos do escalonador
Ret:	==0, se conseguiu
	    >0, caso contrário
-------------------------------------------------------------------*/

int removeAptos(){
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


/*-------------------------------------------------------------------
Função:	Insere thread na fila de bloqueados do escalonador
Ret:	==0, se conseguiu
	!=0, caso contrário
-------------------------------------------------------------------*/

int insereBloqs(TCB_t *thread){
    if(AppendFila2(escalonator->filaBloqs, thread) == 0) {
       printf("Inseriu na fila de Bloqs\n");
       return 0;
    }
    else printf("Oops!");
    return 1;
}

/*-------------------------------------------------------------------
Função:	Remove thread na fila de bloqueados do escalonador
Ret:	==0, se conseguiu
	    >0, caso contrário
-------------------------------------------------------------------*/

int removeBloqs(){
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

void liberaEscalonador(int id){
	//free()
	printf ("liberei escalonador \n");
}

void escalonadorExec(){
	/*Define contexto do escalonador. Se thread acabar, vem para esse contexto*/
	getcontext(escalonator->contexto_escalonador);

	//if(escalonator->threadEmExec->tid != 0){ // 0 == MAIN
	//	liberaEscalonador(escalonator->threadEmExec->tid);
	//	free(escalonator->threadEmExec);
	//}
	//trocaContexto();
    //if(NextFila2(escalonator->filaAptos) == 0)   //se fila não for vazia

	if (FirstFila2(escalonator->filaAptos) == 0){
		printf ("\n!!!!!TROCA CONTEXTO!!!!\n");
		escalonator->threadEmExec = GetAtIteratorFila2(escalonator->filaAptos);
	    if (removeAptos(escalonator) == 0) printf ("   SUCESSO REMOVE APTOS E COLOCA EM EXEC \n");

        //NECESSARIO SETAR CONTEXTO!!!! -> DUVIDAS COM O PROFESSOR EM 16/10/2017 --> RESOLVIDO!
        setcontext(&escalonator->threadEmExec->context);
	}

}

TCB_t* getNextThread()
{
    /*
    tem que retornar o elemetno no começo ou no final da fila (temos que decidir para que lado
    nossa fila vai ser ordenada)
    */
    // tá retornando null só para compilar
    return NULL;

}


/*
void trocaContexto(){
	//if(NextFila2(escalonator->filaAptos) != -1) {  //se fila não for vazia
    //printf ("TROCA CONTEXTO");
		//escalonator->threadEmExec = retiraAptos(escalonator);
		//setcontext(escalonator->threadEmExec->contexto); // executa thread
	//}
*/
/*
TCB_t* createTCB()
{
}
*/
TCB_t* getThreadEmExec()
{
    if(escalonador_iniciado)
        return escalonator->threadEmExec;
    else
        return NULL;
}

Escalonador* getEscalonador()
{
    if(escalonador_iniciado)
        return escalonator;
    else
        return NULL;
}

PFILA2 getFilaAptos()
{
    if(escalonador_iniciado)
        return escalonator->filaAptos;
    else
        return NULL;
}

PFILA2 getFilaBloqs()
{
    if(escalonador_iniciado)
        return escalonator->filaBloqs;
    else
        return NULL;
}


