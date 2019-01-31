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
#include "machine/key.h"
#include "machine/plugbox.h"
#include "machine/pic.h"

#include "guard/gate.h"
#include "guard/guard.h"

#include "device/cgastr.h"

#include "syscall/guarded_semaphore.h"

#define BUF_LEN 64
 
class Keyboard : public Gate, public Keyboard_Controller
{
private:
    Keyboard (const Keyboard &copy); // Verhindere Kopieren

    int x = 0; // to save
    int y = 3; // cursorpos

    Key buffer;

    Guarded_Semaphore semaphore;

public:

    Keyboard();

    // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
    void plugin ();

    /*
     * Unterbrechungsbehandlung der Tastatur. Nicht jede Taste ist auch ein
     * auswertbares ASCII-Zeichen.
     */
    bool prolog(char* msg = "");

    /*
     * In dieser Methode soll das Auftreten des Tastendrucks einem eventuell
     * wartenden Prozess signalisiert werden. Dazu wird ein Semaphor
     * verwendet, dessen Zähler angibt, wieviele Tastaturcodes im
     * Keyboard-Puffer zur Abholung bereitstehen. Wenn ein Puffereintrag
     * überschrieben werden muss, ohne dass der alte Wert von einem
     * Anwendungsprozess abgefragt wurde, darf der Semaphor also nicht
     * hochgezählt werden.
     */
    void epilog();

    /*
     * Diese Methode liefert die zuletzt gedrückte Taste (als Objekt der
     * Klasse Key) zurück. Wenn gerade keine Taste gedrückt wurde, wird der
     * aufrufende Anwendungsprozess solange blockiert. Dies wird durch die
     * Verwendung eines Semaphors erreicht. Sobald der Tastencode abgeholt
     * worden ist, sollte geeignet vermerkt werden, dass der verwendete
     * Puffer nun für den nächsten Tastencode zur Verfügung steht.
     */
    Key getKey();
 };

#endif
