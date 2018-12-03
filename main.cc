/**********************************************************************************************************************/
/* Author:      P. Luettmann, J. Telljohann                                                                           */
/* Version:     2.0                                                                                                   */
/* License:     none                                                                                                  */
/**********************************************************************************************************************/


#include "user/appl.h"
#include "machine/plugbox.h"
#include "device/cgastr.h"
#include "guard/guard.h"
#include "machine/pic.h"


CGA_Stream kout;            // Ausgabeobjekt
Application appl;           // Testanwendung
Plugbox plugbox;            // Plugbox :D
Guard guard;                // Guess what
PIC pic;                    // Programmable interrupt controller

int main()
{
    // "Mopsgeschwindigkeit!"
    appl.action();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
