/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "device/cgastr.h"
#include "device/keyboard.h"
#include "machine/cpu.h"
#include "guard/secure.h"
#include "syscall/thread.h"
#include "syscall/guarded_scheduler.h"

extern CGA_Stream kout;
extern Guarded_Scheduler scheduler;
extern CPU cpu;

class Application : public Thread
 
 {
private:
    Application (const Application &copy); // Verhindere Kopieren

    Thread *ptr1;
    Thread *ptr2;

public:
/* Hier muesst ihr selbst Code vervollstaendigen */
    Application(void *tos) : Thread(tos){
    }

    void killLoop1(Thread *loop){
        this -> ptr1 = loop;
    }

    void killLoop2(Thread *loop){
        this -> ptr2 = loop;
    }
          
    void action ();
 };

#endif
