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
    int count = 2;

    while (count--){
        kout << "\nHier ist Loop mit Zeichen: " << zeichen;
        scheduler.resume();
    }

    kout << endl << "Loop mit Zeichen " << zeichen << " wird abgeschlossen";
    scheduler.exit();
}
 
