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

#include "syscall/thread.h"
#include "device/cgastr.h"
#include "syscall/guarded_scheduler.h"

extern Guarded_Scheduler scheduler;
extern  CGA_Stream kout;

class Loop : public Thread {

public:
    Loop(void* tos) : Thread(tos){}

    void action();
};

#endif
