/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Locker implementiert eine Sperrvariable, die verwendet wird,   */
/* um kritische Abschnitte zu schuetzen. Die Variable zeigt allerdings nur   */
/* an, ob der kritische Abschnitt frei ist. Ein eventuelles Warten und der   */
/* Schutz der fuer diese Klasse notwendigen Zaehlfunktion muss ausserhalb    */
/* erfolgen.                                                                 */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "device/cgastr.h"
#include "device/panic.h"


extern CGA_Stream kout;

class Locker {
private:
    Locker(const Locker &copy); // Verhindere Kopieren

    bool available;

    Panic panic;
public:
    Locker() : available(true){}

    void enter(){
        if(!available){
            kout << "\nalready locked!\n";
            kout.flush();
            panic.prolog();
        }
        /*kout << "\nLocker: locked!\n";
        kout.flush();*/
        available = false;
    }

protected:
    void retne(){
        if(available){
            kout << "\nalready unlocked!\n";
            kout.flush();
            panic.prolog();
        }
        /*kout << "\nLocker: unlocked!\n";
        kout.flush();*/
        available = true;
    }

    bool avail(){
       return available;
    }
};

#endif
