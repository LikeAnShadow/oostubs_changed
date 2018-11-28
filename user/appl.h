/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "device/keyboard.h"
#include "machine/cpu.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

class Application 
 
 {
private:
    Application (const Application &copy); // Verhindere Kopieren

    bool shutdown(char* buf, unsigned int length);
    bool exit(char* buf, unsigned int length);

public:
/* Hier muesst ihr selbst Code vervollstaendigen */
    Application();
          
    void action ();
 };

#endif
