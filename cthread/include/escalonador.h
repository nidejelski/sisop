#ifndef __escalonador__
#define __escalonador__


#include "support.h"
#include "cdata.h"
#include "ucontext.h"

typedef struct sEscalonador{
    PFILA2 filaAptos;
    PFILA2 filaBloqs;
    TCB_t*  threadEmExec; // thread que esta rodando
    //ucontext_t* contexto_escalonador;	// contexto escalonador
} Escalonador;

TCB_t* createTCB();

void setThreademExec(TCB_t* t);

void escalonadorInit();

int insereAptos(TCB_t *thread);

int removeAptos();

int insereBloqs(TCB_t *thread);

int removeBloqs();

void escalonadorExec();

void* execThread(void *(*func)(void*),void *arg);

void trocaContexto();

void liberaEscalonador(int id);

TCB_t* getThreadEmExer();

Escalonador* getEscalonador();

PFILA2 getFilaAptos();

PFILA2 getFilaBloqs();

TCB_t *buscaEmFila(int tid, PFILA2 fila);

TCB_t *existeThread(int tid);


#endif
