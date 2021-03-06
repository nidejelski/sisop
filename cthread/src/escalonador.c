#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "escalonador.h"
#include "cdata.h"
#include "tcb.h"


int escalonador_iniciado = 0;
TCB_t*  threadEmExec; // thread que esta rodando
//int maintcb = 0;


void esca_escalonadorInit(){
    
    if(filas_Init()!=0)
        printf("Erro criando as filas!\n");

    startTimer();
	threadEmExec = NULL;
    escalonador_iniciado = 1;
}



/// será que seria necessário colocar essa função noutro arquivo? 
int esca_dispatcher(){

	if (!filas_aptosVazia()){

        TCB_t* anterior = threadEmExec;
        TCB_t* proxima = (TCB_t*)filas_popAptos();
        startTimer();
        threadEmExec = proxima;
        //NECESSARIO SETAR CONTEXTO!!!! -> DUVIDAS COM O PROFESSOR EM 16/10/2017 --> RESOLVIDO!
        //setcontext(&threadEmExec->context);  /// <<<<<<<<<<<<<<<< acho que tem que ser um swap na verdade
        return swapcontext(&anterior->context, &threadEmExec->context);  /// retorna -1 se erro, e não retorna caso contrário
	}
    return -1;
}


void* esca_execThread(void *(*func)(void*),void *arg)
{
    func(arg);

    //printf("Fim da exec desta thread\n");

    int tidEsperando = filas_isThreadWaitingFor(threadEmExec->tid);
    //printf("threadEmExec->tid = %d e tidEsperando = %d\n", threadEmExec->tid, tidEsperando);
    if(tidEsperando != -1)
    {
        filas_BloqsToAptos(tidEsperando);
    }

    //filas_deletaTcb(threadEmExec->tid);

    tcb_freeTCB(threadEmExec);

    esca_dispatcher();

    //printf("n eh p vir aqui!!!!!!!!!!!!\n");

    return NULL;


}



int esca_terminoThread(TCB_t threadEmExec){    //nao está pronta!
    /*
    threadEmExec->prio = stopTimer();
    threadEmExec->status = PROCST_TERMINO;
    threadEmExec->aguarda_termino = 0;
    //busca aguardada por na lista de blocks e se houver retira de bloqs
    free(threadEmExec);
    */
    return 1; // só para compiular
}


/*  
    ========== getters and setters =========
*/

TCB_t* esca_getThreadEmExec()
{
    return threadEmExec;
}

int esca_getIniciado(){
    return escalonador_iniciado;
}

void esca_setThreademExec(TCB_t* t)
{
    threadEmExec = t;
}


/* 
    \/\/\/\/\/\/\/ ANOTAÇÕES \/\/\/\/\/\/\/v
*/

/*                          <<<<<<<<<<<<<<<<<<<<<<<< fazer ainda
void liberaEscalonador(int id){
    //free()
    printf ("liberei escalonador ?\n");
}
*/



/*   << função de outro trabalho do dispatcher
// realiza o despache de threads
int sched_dispatch(int reschedulecurrent){
    FIFO_t *currentfifo = sched_choose_FIFO();

    if (currentfifo == NULL)
        return -1;

    TCB_t *prevtcb = currenttcb;
    TCB_t *nexttcb = sched_get_next_thread(currentfifo);

    if (nexttcb == NULL)
        return -1;

    if (reschedulecurrent)
        sched_add_thread(currenttcb);

    currenttcb = nexttcb;

    tcb_setstate(currenttcb,MTHREAD_STATE_RUNNING);
    int result = tcb_swapcontext(prevtcb,currenttcb);

    return result;
}
*/
