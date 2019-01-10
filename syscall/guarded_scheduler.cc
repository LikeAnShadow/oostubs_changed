/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ S C H E D U L E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Scheduler.                                  */
/*****************************************************************************/

#include "syscall/guarded_scheduler.h"

void Guarded_Scheduler::ready(Thread &that){
    {
        Secure section;
        Scheduler::ready((Entrant&) that);
    }
}

void Guarded_Scheduler::exit(){
    {
        Secure section;
        Scheduler::exit();
    }

}

void Guarded_Scheduler::kill(Thread &that){
    {
        Secure section;
        Scheduler::kill((Entrant &) that);
    }
}

void Guarded_Scheduler::resume(){
    {
        Secure section;
        kout << endl << "Guarded_Scheduler: resume" << endl;
        kout.flush();
        Scheduler::resume();
    }
}