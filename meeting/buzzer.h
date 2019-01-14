/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

#ifndef __Buzzer_include__
#define __Buzzer_include__

#include "meeting/waitingroom.h"
#include "meeting/bell.h"
#include "syscall/thread.h"
#include "syscall/guarded_organizer.h"
#include "meeting/bellringer.h"

class Buzzer : public Waitingroom, Bell
{
private:
    Buzzer(const Buzzer &copy); // Verhindere Kopieren
public:
    /*
     * Konstruktor. Der Wecker ist zunächst noch abgeschaltet.
     */
    Buzzer();

    /*
     * Im Destruktor wird der Glöckner (Bellringer) informiert, dass er nicht
     * mehr läuten muss. Außerdem werden alle wartenden Threads geweckt.
     */
    virtual ~Buzzer();

    /*
     * Wird vom Glöckner aufgerufen, wenn die Wartezeit abgelaufen ist. Weckt
     * ggfs. schlafende Threads.
     */
    virtual void ring();

    /*
     * Stellen des Weckers.
     */
    void set(int ms);

    /*
     * Schlafen, bis der Wecker klingelt.
     */
    void sleep();
};

#endif
