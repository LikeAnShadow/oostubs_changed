/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Klasse von Objekten, die in der Lage sind, Unterbrechungen zu behandeln.  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

class Gate : public Chain{
private:
    bool isQueued;

public:
    /*
     * Unnötig durch Pro-/Epilog Modell
     */
    //virtual void trigger() = 0;

    Gate(){
       isQueued = false;
    }

    /*
     * Prolog der Unterbrechungsbehandlung. Ein Rückgabewert true zeigt an,
     * dass der zugehörige Epilog ausgeführt werden soll.
     */
    virtual bool prolog() = 0;

    /*
     * Epilogue der Unterbrechungsbehandlung.
     */
    virtual void epilog() {}

    void queued(bool q){
       this -> isQueued = q;
    }

    bool queued(){
       return this -> isQueued;
    }
};
#endif
