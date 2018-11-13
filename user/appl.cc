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

#define BUFFERSIZE 128
         
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
    kc.set_repeat_rate(0xAA,0x01);
    kout.flush();

    char inbuf[128] = {0};
    unsigned char index = 0;
    char zeichen;
    do{
        index = 0;
        do{
            do{
                input = kc.key_hit();
            }while(!input.valid());
            zeichen = input.ascii();
            if(zeichen == '\b'){
                if(index != 0){
                    kout.getpos(x,y);
                    kout.setpos(x-1,y);
                    kout.print(" ", 1);
                    kout.setpos(x-1,y);
                }
            }
            else{
                kout.print(&zeichen, 1);

                if(zeichen == '\n'){
                    inbuf[index] = 0;
                    break;
                }
                else{
                    inbuf[index++] = zeichen;
                    if(index == (BUFFERSIZE-1)){
                        inbuf[index] = 0;
                        index = 0;
                    }
                }
            }
        }while(1);
        if(reboot((char*)inbuf, index)){
            kc.reboot();
        }
    }while(1);
}

bool Application::reboot(char* buf, unsigned int length){
    unsigned int length2 = 6;
    char* code = "reboot";

    if(length2 != length) return false;

    for(int i = 0; i < length; i++){
        if(*(code++) != *(buf++)) return false;
    }
    return true;
}
