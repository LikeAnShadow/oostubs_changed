/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

#include "machine/pic.h"

PIC::PIC() : master(0x21), slave(0xa1){}

PIC::PIC(const PIC &copy) :  master(0x21), slave(0xa1){}

void PIC::allow(int interrupt_device){
   int mask = 0;
   IO_Port *dev;
   // ueberpruefe, ob interrupt_device ein masterdevice ist
   if(interrupt_device <= 7){
      dev = &master;
   }else{
      dev = &slave;
      interrupt_device -= 8;
   }
   // Hole aktuelle maske
   mask = dev->inb();
   // berechne neue maske
   mask &= ~(1<<interrupt_device);
   // setze neue maske
   dev->outb(mask);
}

void PIC::forbid(int interrupt_device){
   int mask = 0;
   IO_Port *dev;
   // ueberpruefe, ob interrupt_device ein masterdevice ist
   if(interrupt_device <= 7){
      dev = &master;
   }else{
      dev = &slave;
      interrupt_device -= 8;
   }
   // Hole aktuelle maske
   mask = dev->inb();
   // berechne neue maske
   mask |= ~(1<<interrupt_device);
   // setze neue maske
   dev->outb(mask);
}

bool PIC::is_masked(int interrupt_device){
   int mask = 0;
   IO_Port *dev;

   if(interrupt_device <= 7){
      dev = &master;
   }else{
      dev = &slave;
      interrupt_device -= 8;
   }
   mask = dev->inb();

   return (mask >> interrupt_device) & 1;
}