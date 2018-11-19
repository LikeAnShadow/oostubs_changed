/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Adresse der  */
/* Behandlungsroutine fuer jeden Hardware-, Softwareinterrupt und jede       */
/* Prozessorexception festlegen.                                             */
/*****************************************************************************/

#ifndef __Plugbox_include__
#define __Plugbox_include__

#include "guard/gate.h"
#include "device/panic.h"

class Plugbox {
public:
    const int timer = 32;
    const int keyboard = 33;

    Plugbox();
    void assign(unsigned int slot, Gate &gate);
    Gate& report(unsigned int slot);
private:
    Plugbox(const Plugbox &copy); // Verhindere Kopieren
    Gate* interruptVectorTable[64]; // Die Interrupt Vektor Tabelle mit 64 Elem.
 };

#endif
