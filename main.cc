/**********************************************************************************************************************/
/* Author:      P. Luettmann, J. Telljohann                                                                           */
/* Version:     2.0                                                                                                   */
/* License:     none                                                                                                  */
/**********************************************************************************************************************/


#include "user/appl.h"


CGA_Stream kout;            // Ausgabeobjekt
Application appl;           // Testanwendung


int main()
{
    // "Mopsgeschwindigkeit!"
    appl.action();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
