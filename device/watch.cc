/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#include "device/watch.h"
#include "guard/guard.h"


extern Plugbox plugbox;
extern Guarded_Scheduler scheduler;
extern PIC pic;
extern Guard guard;

void Watch::windup(){
    plugbox.assign(plugbox.timer, *this); // melde timer an
    pic.allow(PIC::devices::timer); // erlaube interrupts durch timer
}

bool Watch::prolog(){
    return true;
}

void Watch::epilog(){
    /*kout << endl << "Watch: Resume zum naechsten Thread";
    kout.flush();*/
    scheduler.Scheduler::resume();
}

