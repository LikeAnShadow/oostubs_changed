/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/

#include "machine/plugbox.h"

Plugbox::Plugbox(){
   Panic panic; // Panic-Objekt. Wofür? Keine Ahnung

   // Initialisiere interrupt vector table
   for(int i = 0; i < 64; i++){
      this -> assign(i, panic);
   }
}

void Plugbox::assign(unsigned int slot, Gate &gate){
   this -> interruptVectorTable[slot] = &gate;
}

Gate& Plugbox::report(unsigned int slot){
   return *this -> interruptVectorTable[slot];
}