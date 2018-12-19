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

class PIT {
private:
    PIT(const PIT &copy); // Verhindere Kopieren

    int interval;

public:
    /*
     * Im Konstruktor wird der Timer so initialisiert, dass er in Abständen
     * von ca. us Mikrosekunden regelmäßig Unterbrechungen auslöst. Da die
     * Auflösung des Timerbausteins maximal 838 Nanosekunden beträgt, ist
     * keine ganz exakte Einstellung im Mikrosekundenbereich möglich.
     */
    PIT (int us) {
      interval (us);
    }

    /*
     * Gibt an, welches Unterbrechungsintervall eingestellt wurde.
     */
    int interval () {
        return this -> interval;
    }

    /*
     * Stellt das Unterbrechungsintervall neu ein.
     */
    void interval (int us);
};

#endif
