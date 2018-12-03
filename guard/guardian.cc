/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Zentrale Unterbrechungsbehandlungsroutine des Systems.                    */
/* Der Parameter gibt die Nummer des aufgetretenen Interrupts an.            */
/*****************************************************************************/

/* INCLUDES */ // Mehrzahl?
#include "machine/plugbox.h"
#include "guard/guard.h"

/* FUNKTIONEN */
               
extern "C" void guardian (unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

extern Guard guard;
extern Plugbox plugbox;

void guardian (unsigned int slot) {
   if(plugbox.report(slot).prolog()){
      guard.relay(&plugbox.report(slot));
   }
}
