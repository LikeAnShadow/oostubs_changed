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
extern PIC pic;
extern Plugbox plugbox;



Application::Application() {}
         
void Application::action () {
    /*
     * Tests für Aufgabe 1
     */
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
    /*int x,y;

    kout.getpos(x,y);
    kout.setpos(0, y+2);
    kout << "Herzlich Willkommen!\nOOStubSS zu Ihren Diensten..." << endl;
    kout << "Zuerst ein paar Tests.\nTesten wir mal die Zahlenkonvertierung:\n"
            "int 42: " << 42 << "\nhex 42: " << hex << 42 << "\nbin 42: " <<
            bin << 42 << "\noct 42: " << oct << 42 << "\ndec 42: " << dec << 42
            << endl;
    kout << "Weitere Tests.\nTesten wir mal die Zahlenkonvertierung negativer Zahlen:\n"
            "int -42: " << -42 << "\nhex -42: " << hex << -42 << "\nbin -42: " <<
         bin << -42 << "\noct -42: " << oct << -42 << "\ndec -42: " << dec << -42
         << endl;
    kout << "Alles richtig gelaufen?\nAls naechstes wird getestet, ob die "
            "Zeilen nach oben rutschen, wenn mehr als 25 Zeilen geschrieben "
            "werden. Ausserdem sollte ein Zeilenbruch stattfinden, wenn die "
            "Zeilen zu lang werden." << endl;
    kout.flush();
    kout.getpos(x,y);
    kout.print("oostubs:  ", 10);
    kout.setpos(x+9,y);
*/
    /*
     * Dritter Test
     *
     *
     */
    /*Keyboard_Controller kc;
    Key input;
    kc.set_repeat_rate(0xAA,0x01);
    kout.flush();

    unsigned char index = 0;
    char zeichen;
    do{
        char inbuf[128] = {0};
        index = 0;
        do{
            do{
                input = kc.key_hit();
            }while(!input.valid());
            zeichen = input.ascii();
            if(zeichen == '\b'){
                if(index > 0){
                    kout.getpos(x,y);
                    kout.setpos(x-1,y);
                    kout.print(" ", 1);
                    kout.setpos(x-1,y);
                    index--;
                }
            }
            else{
                kout.print(&zeichen, 1);

                if(zeichen == '\n'){
                    kout.print("oostubs:  ", 10);
                    kout.getpos(x,y);
                    kout.setpos(x-1,y);
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
        if(shutdown((char*)inbuf, index)){
            kc.shutdown();
        }
        if(exit((char*)inbuf, index)){
            break;
        }
    }while(1);*/
    /*
     * Tests für Aufgabe 2
     */
    Keyboard keyboard;
    CPU cpu;
    int i = 0, count = 0;
    int x,y;
    char zeichen;
    int wait = 0;

    // Initialisierungen
    keyboard.plugin();
    cpu.enable_int(); // lasse interrupts zu
    while (1){
       i++;
       if(i > 0x2000000){
          //pic.forbid(PIC::devices::keyboard);
          cpu.disable_int();
          i = 0;
          if(count >= 80) count = 0;
          kout.getpos(x,y);
          kout.setpos(79,0);

          while(wait++ < 0x200000);
          wait = 0;
          zeichen = count%10+'0';
          kout.print(&zeichen, 1, kout.GREENONBLACK);
          kout.print(" ", 1);
          kout.setpos(x,y);

          count++;
          //pic.allow(PIC::devices::keyboard);
          cpu.enable_int();
       }
    }
}


bool Application::shutdown(char* buf, unsigned int length){
    unsigned int length2 = 8;
    char* code = "shutdown";

    if(length2 != length) return false;

    for(unsigned int i = 0; i < length; i++){
        if(*(code++) != *(buf++)) return false;
    }
    return true;
}

bool Application::exit(char* buf, unsigned int length){
    unsigned int length2 = 4;
    char* code = "exit";

    if(length2 != length) return false;

    for(unsigned int i = 0; i < length; i++){
        if(*(code++) != *(buf++)) return false;
    }
    return true;
}
