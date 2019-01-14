/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

#include "meeting/waitingroom.h"
#include "thread/customer.h"

Waitingroom::~Waitingroom(){}

void Waitingroom::remove(Customer* customer){
    // Sicherheitsabfrage, falls null
    if(!customer) return;
    // Wenn nicht null, dann entfernen mit der Methode von Queue
    Queue::remove(customer);
}