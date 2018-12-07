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

/* INCLUDES */
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "device/cgastr.h"

/* FUNKTIONEN */
               
extern "C" void guardian (unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

extern Guard guard;
extern Plugbox plugbox;
extern CGA_Stream kout;

void guardian (unsigned int slot) {
   if(plugbox.report(slot).prolog()){
      guard.relay(&plugbox.report(slot));
   }/* else{
      kout << "Prolog liefert false\n\n";
      kout.flush();
   }*/
}
