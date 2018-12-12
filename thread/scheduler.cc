/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#include "thread/scheduler.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

Scheduler::Scheduler(const Scheduler &copy){}

void Scheduler::ready (Entrant &that){
    kout << "\nScheduler: ready";
    kout.flush();
    list.enqueue(&that);
}

void Scheduler::schedule(){
    kout << "\nScheduler: schedule";
    kout.flush();
    // Hole nächstes
    Entrant *next = (Entrant*)list.dequeue();

    if(!next) return;

    // dispatchen
    go(*next);
}

void Scheduler::exit(){
    kout << "\nScheduler: exit";
    kout.flush();
    Entrant *next = (Entrant*)list.dequeue();

    if(!next) while(1);

    dispatch(*next);
}

void Scheduler::kill(Entrant &that){
    kout << "\nScheduler: kill";
    kout.flush();
    // Einfach aus der Liste löschen... fertig
    list.remove(&that);
}

void Scheduler::resume(){
    kout << "\nScheduler: resume";
    kout.flush();
    Entrant *ptr;

    // Zeiger auf aktuellen Thread setzen
    ptr = (Entrant*)active();

    if(!ptr) return;

    // aktuellen Prozess in die Liste eintragen
    list.enqueue(ptr);

    // nächsten Prozess holen
    ptr = (Entrant*)list.dequeue();

    if(!ptr) return;

    // aktiviere Prozess
    dispatch(*ptr);
}