/**********************************************************************************************************************/
/* Author:      P. Luettmann, J. Telljohann                                                                           */
/* Version:     2.0                                                                                                   */
/* License:     none                                                                                                  */
/**********************************************************************************************************************/


#include "user/appl.h"
#include "machine/plugbox.h"


CGA_Stream kout;            // Ausgabeobjekt
Application appl;           // Testanwendung
Plugbox plugbox;            // Plugbox :D


int main()
{
    // "Mopsgeschwindigkeit!"
    appl.action();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
