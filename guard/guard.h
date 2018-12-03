/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/

#ifndef __Guard_include__
#define __Guard_include__

// INCLUDES
#include "guard/locker.h"
#include "guard/gate.h"
#include "machine/cpu.h"
#include "object/queue.h"

class Guard : public Locker {

private:
    Guard (const Guard &copy); // Verhindere Kopieren

    // Queue zum anhängen der gates;
    Queue gates;

public:
    Guard ();

    // zum Verlassen des kritischen Abschnittes
    void leave();

    // Damit wird ein Prozess angehängt. Wird von guardian aufgerufen
    void relay(Gate *item);
};

#endif
