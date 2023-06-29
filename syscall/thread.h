/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             T H R E A D                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Benutzerschnittstelle eines Threads.                                      */
/*****************************************************************************/

#ifndef __thread_include__
#define __thread_include__

#include "thread/customer.h"

class Thread : public Customer {
private:
    Thread (const Thread &copy); // Verhindere Kopieren

    unsigned char* returnAddress() {
        unsigned char stack[4096];
        unsigned char* p = stack;
        return p;
    }
public:
    /*
     * Der Konstruktor leitet den Parameter tos an den Konstruktor der
     * Basisklasse Customer weiter.
     */
    Thread(char h = 'a') : Customer(returnAddress()){}
 };

#endif
