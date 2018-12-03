/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/

#include "guard/guard.h"


Guard::Guard() : Locker() {}

/*
 * Kritischer Abschnitt wird verlassen und Epiloge in der chain werden
 * bearbeitet
 */
void Guard::leave(){
   CPU cpu;

   // kurzfristiges Verbieten der Interrupts, damit items verändert werden
   // können, ohne dass zwischenzeitliche Interrupts den Vorgang beeinflussen
   cpu.disable_int();
   Gate *item = (Gate*)gates.dequeue();

   while(item){
      item -> queued(false);

      cpu.enable_int();
      item -> epilog();

      cpu.disable_int();
      item = (Gate*)gates.dequeue();
   }

   this -> retne();
   cpu.enable_int();
}


/*
 * Wird von guardian aufgerufen, wenn prolog() true geliefert hat
 */
void Guard::relay(Gate *item){
   CPU cpu;

   if(avail()){
      enter();
      cpu.enable_int();
      item -> epilog();
      leave();
   } else{
      if(!item -> queued()){
         gates.enqueue((Chain*)item);
         item -> queued(true);
      }
   }
}