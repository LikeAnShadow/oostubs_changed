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

Panic panic;

Plugbox::Plugbox(){

   // Initialisiere interrupt vector table
   for(int i = 0; i < 64; i++){
      this -> assign(i, panic);
   }
}

void Plugbox::assign(unsigned int slot, Gate &gate){
   if(slot < 64 && slot >= 0){
      this -> interruptVectorTable[slot] = &gate;
   } else{
      panic.prolog();
   }
}

Gate& Plugbox::report(unsigned int slot){
   return *this -> interruptVectorTable[slot];
}