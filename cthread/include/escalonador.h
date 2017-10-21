#ifndef __escalonador__
#define __escalonador__

#include "cdata.h"


/// inicializa algumas variáveis necessárias 
void esca_escalonadorInit();

/// faz o dispatch de threads. Retorna -1 caso de erro.
int esca_dispatcher();

/// função que executa uma thread
void* esca_execThread(void *(*func)(void*),void *arg);


int esca_getIniciado();

void esca_setThreademExec(TCB_t* t);

TCB_t* esca_getThreadEmExec();


#endif
