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

Dispatcher::Dispatcher(){
    this -> ptr = 0;
}

void Dispatcher::go(Coroutine &first){
    // Prozess speichern
    this -> ptr = &first;
    // Prozess ausführen
    first.go();
}

void Dispatcher::dispatch(Coroutine &next){
    // aktuellen Prozess zwischenspeichern
    Coroutine *temp = this -> ptr;

    if(!this -> ptr) return;

    // Pointer neu setzen
    this -> ptr = &next;

    // Koroutinenwechsel
    temp -> resume();
}

Coroutine* Dispatcher::active(){
    return this -> ptr;
}