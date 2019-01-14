/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#include "panic.h"

extern CGA_Stream kout;


bool Panic::prolog(char* msg){
   // Zuerst die Fehlermeldung, genau wie in Trigger -> eZ
   if(!msg){
      kout << "ALARM! Ein wildes Interrupt taucht auf! Was soll ich nur tun?\n";
      kout << "-> Ich habs! Ich halte die komplette CPU einfach an";
   }else{
      kout << endl << msg << endl;
   }
   kout.flush();

   // Dann CPU anhalten
   CPU cpu;
   cpu.halt();
   return false;
}