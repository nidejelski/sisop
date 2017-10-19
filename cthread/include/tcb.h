#ifndef __tcb__
#define __tcb__

#include <stdlib.h>
#include <stdio.h>
#include "cdata.h"
#include "cthread.h"

TCB_t* createTCB(int tid);

void createContext(TCB_t* t,void* exec, void* func, void* arg, int tamPilha);

#endif

