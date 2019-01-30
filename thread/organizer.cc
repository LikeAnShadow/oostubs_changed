/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Organizer ist ein spezieller Scheduler, der zusaetzlich das Warten    */
/* von Threads (Customer) auf Ereignisse erlaubt.                            */
/*****************************************************************************/

#include "thread/organizer.h"

void Organizer::block(Customer& customer, Waitingroom& waitingroom){
    // schiebe customer in waitingroom
    waitingroom.enqueue(&customer);

    // soll aktiver Prozess blockiert werden
    if(&customer == active()){
        // dann setze ihn nicht auf ready
        exit();
    } else{
        // sonst lösche ihn von der ready-liste
        kill(customer);
    }
}

void Organizer::wakeup(Customer& customer){
    // hole waitingroom von customer
    Waitingroom* w = customer.waiting_in();
    if(w){
        // damit er daraus gelöscht werden kann
        w -> remove(&customer);
    }
    // und Zustand zurücksetzen
    customer.waiting_in(0);
    // zuletzt in die ready-liste einfügen
    Scheduler::ready(customer);
}

void Organizer::kill(Customer& that){
    // ist that im waitingroom
    Waitingroom* w = that.waiting_in();
    if(w){
        // lösche ihn daraus
        w -> remove(&that);
    }else{
        // wenn er nicht im waitingroom ist
        // ist er active?
        if(&that == active()){
            // verhindere, dass er auf die ready-liste kommt
            exit();
        } else{
            // sonst ist er auf der ready-liste
            // dann lösche ihn von dort
            Scheduler::kill(that);
        }
    }
}