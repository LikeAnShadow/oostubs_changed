/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            E N T R A N T                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Eine Koroutine, die vom Scheduler verwaltet wird.                         */
/*****************************************************************************/

#ifndef __entrant_include__
#define __entrant_include__

#include "thread/coroutine.h"
#include "object/chain.h"
#include "device/cgastr.h"

extern CGA_Stream kout;

class Entrant : public Coroutine, public Chain{
private:
    Entrant (const Entrant &copy); // Verhindere Kopieren

public:
    /*
     * Der Entrant Konstruktor gibt nur den Parameter tos an den Coroutinen
     * Konstruktor weiter.
     */
    Entrant (void *tos)
        : Coroutine(tos){
    }
};

#endif
