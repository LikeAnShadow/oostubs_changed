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
    int wait = 10000;
    int count = 0;
    Guarded_Buzzer buzzer;

    //Endlosschleife
    while(1) {
        kout.setpos(0,2);
        kout << "Loop: Doing stuff("<< count++ << ")";
        kout.flush();

        while (wait-- > 0);
        wait = 10000;
        /*buzzer.set(10000);
        buzzer.sleep();*/
    }

}
 
