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
            //panic.prolog("already locked");
        }
        /*kout << "\nLocker: locked!\n";
        kout.flush();*/
        available = false;
    }

    bool avail(){
        return available;
    }

protected:
    void retne(){
        if(available){
            //panic.prolog("already unlocked");
        }
        /*kout << "\nLocker: unlocked!\n";
        kout.flush();*/
        available = true;
    }


};

#endif
