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

/* INCLUDES */
#include "meeting/buzzer.h"

extern Guarded_Organizer guarded_organizer;
extern Bellringer bellringer;

Buzzer::Buzzer(){}

Buzzer::~Buzzer(){
    bellringer.cancel(this);
    Thread *thread = (Thread*)dequeue();

    while(thread)
    {
        thread -> waiting_in(0);
        guarded_organizer.ready(*thread);
        thread = (Thread*)dequeue();
    }
}

// Genau wie Destructor, nur ohne cancel
void Buzzer::ring(){
    Thread *thread = (Thread*)dequeue();

    while(thread)
    {
        thread -> waiting_in(0);
        guarded_organizer.ready(*thread);
        thread = (Thread*)dequeue();
    }
}

void Buzzer::set (int ms)
{
    bellringer.job(this, ms);
}

void Buzzer::sleep ()
{
    Thread *thread = (Thread*)guarded_organizer.active();
    guarded_organizer.block(*thread, *this);
}