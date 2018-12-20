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

    int wait = 0;
    Keyboard keyboard;
    keyboard.plugin();

    kout.setpos(0,0);

    //resume
    kout << "Appl: Pause";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //nochmal resume
    kout << endl << "Appl: Pause";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //nochmal resume
    kout << endl << "Appl: Pause";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //Kill
    kout << "\nAppl: Loop wird abgeschossen mit kill";
    kout.flush();
    scheduler.kill(*ptr1);

    //resume
    kout << endl << "Appl: Pause";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //Exit
    kout << endl << "Appl: Terminierung";
    kout.flush();

    wait=100000000;
    while(wait) wait--;

    scheduler.exit();

    //Ausgabe wenn fehlerhaft
    kout << endl << "Appl: Ausgabe trotz Terminierung!";
}
