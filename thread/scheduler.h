/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der Scheduler verwaltet die Ready-Liste (ein privates Queue-Objekt der    */
/* Klasse), also die Liste der lauffähigen Prozesse vom Typ Entrant. Die     */
/* Liste wird von vorne nach hinten abgearbeitet. Dabei werden Prozesse, die */
/* neu im System sind oder den Prozessor abgeben, stets an das Ende der Liste*/
/* angefügt.                                                                 */
/*****************************************************************************/

#ifndef __schedule_include__
#define __schedule_include__

#include "thread/dispatch.h"
#include "thread/entrant.h"
#include "thread/coroutine.h"
#include "object/queue.h"

class Scheduler : public Dispatcher{
private:
    Scheduler (const Scheduler &copy); // Verhindere Kopieren

    Queue list;
public:
    Scheduler(){}
    /*
     * Mit dieser Methode wird der Prozess that beim Scheduler angemeldet. Er
     * wird an das Ende der Ready-Liste angefügt.
     */
    void ready (Entrant &that);

    /*
     * Diese Methode setzt das Scheduling in Gang, indem der erste Prozess
     * von der Ready-Liste entfernt und aktiviert wird.
     */
    void schedule ();

    /*
     * Hiermit kann sich ein Prozess selbst beenden. Er wird nun nicht wieder
     * an das Ende der Ready-Liste angefügt. Statt dessen wird nur der erste
     * Prozess von der Ready-Liste heruntergenommen und aktiviert.
     */
    void exit ();

    /*
     * Mit dieser Methode kann ein Prozess einen anderen (that) beenden. Der
     * Prozess that wird einfach von der Ready-Liste entfernt und erhält
     * somit nie wieder den Prozessor.
     */
    void kill (Entrant &that);

    /*
     * Hiermit kann ein Prozesswechsel ausgelöst werden, ohne dass der
     * aufrufende Entrant wissen muss, welche anderen Entrant Objekte im
     * System existieren und welcher davon sinnvollerweise aktiviert werden
     * sollte. Diese Entscheidung trifft der Scheduler anhand der Einträge
     * seiner Ready-Liste. Im derzeitigen System soll er den gerade laufenden
     * Prozess an das Ende der Ready-Liste anfügen und den ersten aktivieren.
     */
    void resume ();
};

#endif
