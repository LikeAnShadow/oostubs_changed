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

         
void Application::action () {
    int wait = 1000000;
    int count = 0;
    Guarded_Buzzer buzzer;

    kout.setpos(0,0);

    kout << "Appl: First!";
    kout.flush();

    while (1){
        kout.setpos(0,1);
        kout << "Appl: Doing important stuff(" << count++ << ")";
        kout.flush();

        while (wait-- > 0);
        wait = 1000000;
    }
}
