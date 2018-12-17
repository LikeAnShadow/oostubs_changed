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

#define BUFFERSIZE 128
         
/* GLOBALE VARIABLEN */
extern Scheduler scheduler;

         
void Application::action () {

    CPU cpu;

    // Initialisierungen
    kout.setpos(0,0);

    cpu.enable_int();

    kout << "Test: Starte Loop-routinen. Es sollten a und b ausgegeben werden";
    kout.flush();
    scheduler.resume();

    kout << endl << "Test: Starte zweite Loop-routine. Selbes Ergebnis";
    kout.flush();
    scheduler.resume();

    kout << endl << "Test: Kill a-Loop aus dem Scheduler. Sollte nicht mehr"
                    " auftauchen";
    kout.flush();
    scheduler.kill(*ptr1);

    kout << endl << "Test: b-Loop sollte jetzt beenden";
    kout.flush();
    scheduler.resume();

    kout << endl << "Test: Terminiere alle noch anstehenden Threads. Es "
                    "sollten keine Ausgaben mehr kommen";
    kout.flush();
    scheduler.exit();

    // Sollte nicht mehr erreicht werden
    kout << endl << "Test: Es wurde trotzdem noch eine Ausgabe gemacht";
    kout.flush();
}
