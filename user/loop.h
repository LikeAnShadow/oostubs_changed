/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab.                                                         */
/*****************************************************************************/

#ifndef __loop_include__
#define __loop_include__

#include "thread/entrant.h"
#include "device/cgastr.h"
#include "thread/scheduler.h"

extern Scheduler scheduler;
extern  CGA_Stream kout;

class Loop : public Entrant {

public:
    Loop(void* tos, char zeichen) : Entrant(tos){
        this -> zeichen = zeichen;
    }

    void action();

private:

    char zeichen;
};

#endif
