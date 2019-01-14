/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop ist ein Thread, der nichts weiter tut als einen Zaehler hochzu-      */
/* zaehlen und dies auf dem Bildschirm anzuzeigen. Zwischendurch gibt er     */
/* den Prozessor ab. Der Scheduler bestimmt dann, welcher Thread als         */
/* naechstes laufen soll.                                                    */
/*****************************************************************************/

#include "user/loop.h"

void Loop::action(){
    int wait;
    int count = 0;

    //Endlosschleife
    while(1) {
        kout.setpos(0,2);
        kout << "Loop: Doing stuff("<< count++ << ")";
        kout.flush();

        wait = 100000000;
        while (wait > 0) wait--;
    }

}
 
