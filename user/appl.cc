/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "syscall/guarded_semaphore.h"

extern Guarded_Semaphore waiter;

         
void Application::action () {
    int wait = 10000;
    int count = 0;
    Guarded_Buzzer buzzer;

    kout.setpos(0,0);
    kout << "Appl: First!";
    kout.flush();

    while (1){
        waiter.wait();
        kout.setpos(0,1);
        kout << "Appl: Doing important stuff(" << count++ << ")";
        kout.flush();
        waiter.signal();

        //buzzer.set(1000);
        //buzzer.sleep();

        while (wait-- > 0);
        wait = 10000;
    }
}
