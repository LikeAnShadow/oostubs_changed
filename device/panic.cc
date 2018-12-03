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

/*
void Panic::trigger() {
   // Zuerst die Fehlermeldung
   kout << "ALARM! Ein wildes Interrupt taucht auf! Was soll ich nur tun?\n";
   kout << "-> Ich habs! Ich halte die komplette CPU einfach an";

   // Dann CPU anhalten
   CPU cpu;
   cpu.halt();
}
*/

bool Panic::prolog(){
   // Zuerst die Fehlermeldung, genau wie in Trigger -> eZ
   kout << "ALARM! Ein wildes Interrupt taucht auf! Was soll ich nur tun?\n";
   kout << "-> Ich habs! Ich halte die komplette CPU einfach an";

   // Dann CPU anhalten
   CPU cpu;
   cpu.halt();
}