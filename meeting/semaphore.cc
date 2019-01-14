/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#include "meeting/semaphore.h"
#include "syscall/guarded_organizer.h"
#include "device/panic.h"
#include "device/cgastr.h"

extern Panic panic;
extern Guarded_Organizer guarded_organizer;
extern CGA_Stream kout;

Semaphore::Semaphore(int c){
    count = c;
}

void Semaphore::p(){
    // aktuell aktiver Thread
    Customer *act;

    // Wenn count unter 0 fällt, wird aktueller Thread in den Warteraum gesetzt
    if(--count < 0){
        act = (Customer*)(guarded_organizer.active());
        guarded_organizer.block(*act, *this);
    }
}

void Semaphore::v(){
    // nächster Thread
    Customer *next;

    // Wennt mindestens ein Customer im Warteraum ist, wird der erste von den
    // möglichen Wartenden aufgeweckt
    if(++count <= 0){
        next = (Customer*)this->dequeue();
        // Sicherheitsabfrage
        // Panik angebracht, oder lieber stiller Abbruch?
        if(!next){
            panic.prolog("Der Warteraum ist leer!");
        }else{
            guarded_organizer.wakeup(*next);
        }
    }
}