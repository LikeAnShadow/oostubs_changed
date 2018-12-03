/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "device/cgastr.h"
#include "guard/guard.h"
 
class Keyboard : public Gate, public Keyboard_Controller
{
private:
      Keyboard (const Keyboard &copy); // Verhindere Kopieren

      char zeichen;
public:

    Keyboard();

    // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
    void plugin ();

    /*
     * Diese Methode ist unnötig, sobald das Pro-/Epilog Modell implementiert
     * wurde
     */
    //void trigger();

    /*
     * Unterbrechungsbehandlung der Tastatur. Nicht jede Taste ist auch ein
     * auswertbares ASCII-Zeichen.
     */
    bool prolog();

    void epilog();
 };

#endif
