#ifndef __tcb__
#define __tcb__

#include <stdlib.h>
#include <stdio.h>
#include "cdata.h"
#include "cthread.h"

TCB_t* tcb_createTCB(int tid);

void tcb_createContext(TCB_t* t,void* exec, void* func, void* arg, int tamPilha);

#endif

