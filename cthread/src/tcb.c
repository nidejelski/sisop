#include "tcb.h"

TCB_t* tcb_createTCB(int tid)
{

    TCB_t* t = malloc(sizeof(TCB_t));
    //t->context = contextoNovo;
    t->tid = tid;
    t->prio = 0;
    t->state = PROCST_CRIACAO;

    t->context.uc_link = NULL;
    t->context.uc_stack.ss_sp = NULL;
    t->context.uc_stack.ss_size = 0;

    return t;
}

void tcb_createContext(TCB_t* t,void* exec, void* func, void* arg, int tamPilha)
{
    getcontext(&t->context);

    t->context.uc_stack.ss_sp = malloc(tamPilha);
    t->context.uc_stack.ss_size = tamPilha;

    makecontext(&t->context,exec,2,func,arg);
}


void tcb_freeTCB(TCB_t* t)
{
    if(t->context.uc_stack.ss_sp != NULL)
        free(t->context.uc_stack.ss_sp);
    free(t);
}