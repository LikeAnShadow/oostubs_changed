/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Dispatcher.                                           */
/* Der Dispatcher verwaltet den life-Pointer, der die jeweils aktive         */
/* Koroutine angibt. mit go() wird der life Pointer initialisiert und die    */
/* erste Koroutine gestartet, alle weiteren Kontextwechsel werden mit        */
/* dispatch() ausgeloest. active() liefert den life Pointer zurueck.         */
/*****************************************************************************/

#include "thread/dispatch.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

Dispatcher::Dispatcher(){
    this -> ptr = 0;
}

void Dispatcher::go(Coroutine &first){
    kout << endl << "Dispatcher: go";
    kout.flush();
    // Prozess speichern
    this -> ptr = &first;
    // Prozess ausführen
    first.go();
}

void Dispatcher::dispatch(Coroutine &next){
    kout << endl << "Dispatcher: dispatch";
    kout.flush();
    // aktuellen Prozess zwischenspeichern
    Coroutine *temp = this -> ptr;

    if(!this -> ptr) return;

    // Pointer neu setzen
    this -> ptr = &next;

    // Koroutinenwechsel
    temp -> resume(*temp);
}

Coroutine* Dispatcher::active(){
    kout << endl << "Dispatcher: active";
    kout.flush();
    return this -> ptr;
}