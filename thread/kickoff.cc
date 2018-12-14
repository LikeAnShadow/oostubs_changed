/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K I C K O F F                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Funktion zum Starten einer Koroutine.                                     */
/* Da diese Funktion nicht wirklich aufgerufen, sondern nur durch eine       */
/* geschickte Initialisierung des Stacks der Koroutine angesprungen wird,    */
/* darf sie nie terminieren. Anderenfalls wuerde ein sinnloser Wert als      */
/* Ruecksprungadresse interpretiert werden und der Rechner abstuerzen.       */
/*****************************************************************************/

#ifndef __KICKOFF_CC
#define __KICKOFF_CC

#include "thread/coroutine.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

/**
 * Diese Methode realisiert den Sprung von der C Ebene zur
 * C++ Ebene, indem sie ganz einfach die Methode action()
 * des als Parameter vorgefundenen Koroutinenobjektes object aufruft.
 */
void kickoff (void *dummy1, void *dummy2, void *dummy3, void *dummy4,
        void *dummy5, void *dummy6, Coroutine* object)
{
    //kout << endl << "Kickoff: application is:  ";
    //kout << object;
    //kout.flush();
    object->action();
}

#endif	//__KICKOFF_CC