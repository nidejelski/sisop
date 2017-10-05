#include "support.h"
#include "cdata.h"
#include "ucontext.h"

struct Escalonador{
    PFILA2 filaAptos;
    PFILA2 filaBloqs;
    s_TCB* threadEmExec; // thread que esta rodando
    ucontext_t* contexto_escalonador;	// contexto escalonador
};


Escalonador* escalonadorInit();

int insereAptos(Escalonador* escalonator,s_TCB *thread);

s_TCB* retiraAptos(Escalonador* escalonator);

int insereBloqs(Escalonador* escalonator,s_TCB *thread);

s_TCB* retiraBloqs(Escalonador* escalonator);

void escalonadorExec();

void trocaContexto();

void liberaEscalonador(int id);
