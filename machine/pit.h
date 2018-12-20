/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "machine/io_port.h"

#define PI 3.14159265358979323846  /* pi */

class PIT {
private:
    PIT(const PIT &copy); // Verhindere Kopieren

    IO_Port steuerregister;
    IO_Port zaehler;

    int us;

public:
    /*
     * Im Konstruktor wird der Timer so initialisiert, dass er in Abständen
     * von ca. us Mikrosekunden regelmäßig Unterbrechungen auslöst. Da die
     * Auflösung des Timerbausteins maximal 838 Nanosekunden beträgt, ist
     * keine ganz exakte Einstellung im Mikrosekundenbereich möglich.
     */
    PIT (int us) : steuerregister(0x43), zaehler(0x40){
      interval (us);
    }

    /*
     * Gibt an, welches Unterbrechungsintervall eingestellt wurde.
     */
    int interval () {return this -> us;}

    /*
     * Stellt das Unterbrechungsintervall neu ein.
     */
    void interval (int us);
};

#endif
