/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"

         
/* GLOBALE VARIABLEN */
extern CGA_Stream kout;


Application::Application() {}
         
void Application::action () {
    /*int x,y;
    kout.getpos(x,y);
    kout.setpos(x,y+9);
    // Gibt eine seltsame Ausgabe aus
    kout << "Hallo Welt" << endl << "Das funktioniert ja ganz ok" << endl;
    kout.flush();*/
    Keyboard_Controller kc;
    Key input;

    char inbuf[100] = {0};
    unsigned char index = 0;
    char zeichen;

    kc.set_repeat_rate(0xFF, 0x03);
    kout << "Guten Tag,\n das ist OOSTUBS, ein kleines OS von Stundenten fuer Studenten";
    kout << endl;
    kout.flush();


}
