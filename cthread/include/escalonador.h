#ifndef __escalonador__
#define __escalonador__

#include "support.h"
#include "cdata.h"
#include "ucontext.h"

typedef struct sEscalonador{
    PFILA2 filaAptos;
    PFILA2 filaBloqs;
    TCB_t*  threadEmExec; // thread que esta rodando
    ucontext_t* contexto_escalonador;	// contexto escalonador
} Escalonador;

Escalonador* escalonadorInit();

int insereAptos(Escalonador* escalonator, TCB_t *thread);

TCB_t* retiraAptos(Escalonador* escalonator);

int insereBloqs(Escalonador* escalonator, TCB_t *thread);

TCB_t* retiraBloqs(Escalonador* escalonator);

void escalonadorExec();

void trocaContexto();

void liberaEscalonador(int id);


#endif
