/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          C O R O U T I N E                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Koroutinenkonzepts.                                   */
/* Im Konstruktor wird der initiale Kontext der Koroutine eingerichtet.      */
/* Mit go() wird die erste Koroutine aktiviert. Alle weiteren Koroutinen-    */
/* wechsel sollten mit resume() erfolgen.                                    */
/* Um bei einem Koroutinenwechsel den Kontext sichern zu koennen, enthaelt   */
/* jedes Koroutinenobjekt eine Struktur toc, in dem die Werte der nicht-     */
/* fluechtigen Register gesichert werden koennen.                            */
/*****************************************************************************/

#include "thread/coroutine.h"
#include "device/cgastr.h"

// Funktionen, die auf der C- oder Assembler-Ebene implementiert werden,
// muessen als extern "C" deklariert werden, da sie nicht dem Name-Mangeling
// von C++ entsprechen.
extern "C" {
   void toc_go (struct toc* regs);
   void toc_switch (struct toc* regs_now, struct toc* regs_then);
   void toc_settle (struct toc* regs, void* tos, void (*kickoff)(void*, void*,
                  void*, void*, void*, void*, Coroutine*), void* object);
}

extern void kickoff(void*, void*, void*, void*, void*, void*, Coroutine*);

extern CGA_Stream kout;

Coroutine::Coroutine(void* tos){
    //kout << endl << "Coroutine: toc_settle";
    //kout.flush();
    toc_settle( &this -> toc1, tos, &kickoff, this);
}

void Coroutine::go(){
    //kout << endl << "Coroutine: go";
    //kout.flush();
    toc_go(&this->toc1);
    //kout << endl << "Coroutine: go finished";
    //kout.flush();
}

void Coroutine::resume (Coroutine& next) {
    //kout << endl << "Coroutine: toc_switch";
    //kout.flush();
    toc_switch(&(this->toc1), &(next.toc1));
    //kout << endl << "Coroutine: resume";
    //kout.flush();
}