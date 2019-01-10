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
    kout << "Appl: Hier bin ich! 1";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //nochmal resume
    kout << endl << "Appl: Hier bin ich! 2";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //nochmal resume
    kout << endl << "Appl: Hier bin ich! 3";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //Kill
    kout << "\nAppl: Loop wird abgeschossen mit kill";
    kout.flush();
    scheduler.Scheduler::kill(*ptr1);

    //resume
    kout << endl << "Appl: Hier bin ich! 4";
    kout.flush();
    wait=100000000;
    while(wait) wait--;

    //Exit
    kout << endl << "Appl: Terminierung" << endl;
    kout.flush();

    wait=100000000;
    while(wait) wait--;

    scheduler.Scheduler::exit();

    //Ausgabe wenn fehlerhaft
    kout << endl << "Appl: Ausgabe trotz Terminierung!";
}
