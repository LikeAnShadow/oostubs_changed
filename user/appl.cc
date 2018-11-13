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
    /*Erster Test
     *
     *
     * \
    /*int x,y;
    kout.getpos(x,y);
    kout.setpos(x,y+9);
    // Gibt eine seltsame Ausgabe aus
    kout << "Hallo Welt" << endl << "Das funktioniert ja ganz ok" << endl;
    kout.flush();*/


    /*
     * Zweiter Test
     *
     *
     */
    int x,y;

    kout.getpos(x,y);
    kout.setpos(0, y+2);
    kout << "Herzlich Willkommen!\nOOStubSS zu Ihren Diensten..." << endl;
    kout << "Zuerst ein paar Tests.\nTesten wir mal die Zahlenkonvertierung:\n"
            "int 42: " << 42 << "\nhex 42: " << hex << 42 << "\nbin 42: " <<
            bin << 42 << "\noct 42: " << oct << 42 << "\ndec 42: " << dec << 42
            << endl;
    kout << "int -25500: " << dec << -25500 << oct<< "\noct: " << -25500 <<
    "\nhex: " << hex << -25500 << endl;
    kout << "Alles richtig gelaufen?\nAls naechstes wird getestet, ob die "
            "Zeilen nach oben rutschen, wenn mehr als 25 Zeilen geschrieben "
            "werden. Ausserdem sollte ein Zeilenbruch stattfinden, wenn die "
            "Zeilen zu lang werden." << endl;
    kout.flush();

    /*
     * Dritter Test
     *
     *
     */
    Keyboard_Controller kc;
    Key input;
    kc.set_repeat_rate(0xFF,0x03);
    kout.flush();

    char inbuf[100] = {0};
    unsigned char index = 0;
    char zeichen;
    int BUFSIZE = 100;
    do{
        do{
            input = kc.key_hit();
        }while(!input.valid());
        zeichen = input.ascii();
        if(zeichen == '\n'){
            kout.getpos(x,y);
            kout.setpos(0,y+1);
        }
        else if(zeichen == '\b'){
            kout.getpos(x,y);
            kout.setpos(x-1,y);
            kout.print(" ", 1);
            kout.setpos(x-2,y);
        }
        else{
            kout.print(&zeichen, 1);
            inbuf[index++] = zeichen;
        }
    }while(index < BUFSIZE);
    kout << inbuf << endl;


}
