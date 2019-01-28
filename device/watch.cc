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
extern Guarded_Organizer guarded_organizer;
extern PIC pic;
extern Guard guard;
extern Bellringer bellringer;

void Watch::windup(){
    plugbox.assign(plugbox.timer, *this); // melde timer an
    pic.allow(PIC::devices::timer); // erlaube interrupts durch timer
}

bool Watch::prolog(char* msg){
    return true;
}

void Watch::epilog(){
    /*kout << endl << "Watch: Resume zum naechsten Thread";
    kout.flush();*/
    bellringer.check();
    guarded_organizer.resume();
}

