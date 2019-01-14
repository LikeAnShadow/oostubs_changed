/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Waitingroom implementiert eine Liste von Prozessen (Customer   */
/* Objekten), die alle auf ein bestimmtes Ereignis warten.                   */
/*****************************************************************************/

#ifndef __waitingroom_include__
#define __waitingroom_include__

#include "object/queue.h"

class Customer; // Forward declaration

class Waitingroom 
 : public Queue
{
private:
    Waitingroom(const Waitingroom &copy); // Verhindere Kopieren
public:
    Waitingroom() {}

    /*
     * Der Destruktor entfernt alle noch wartenden Prozesse von der Liste und
     * weckt sie zudem auf.
     */
    virtual ~Waitingroom();

    /*
     * Mit dieser Methode kann der angegebene Prozess customer vorzeitig aus
     * dem Wartezimmer entfernt werden.
     */
    virtual void remove(Customer* customer);
};

#endif
