/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#include "device/keyboard.h"

extern Plugbox plugbox;
extern CGA_Stream kout;
extern PIC pic;
extern Guard guard;

Keyboard::Keyboard() : Gate(), Keyboard_Controller(), zeichen(0), semaphore
(0) {}

void Keyboard::plugin(){
   plugbox.assign(plugbox.keyboard, *this); // melde keyboard an
   pic.allow(PIC::devices::keyboard); // erlaube unterbrechungen von keyboard

   //initialisiere integer
   this -> limit = 0;
   this -> head = 0;
   this -> tail = 0;
   this -> key.ascii(0);

   return;
}

bool Keyboard::prolog(char* msg){
   char zeichen;
   Key input;

   input = this -> key_hit();
   if(input.valid()){
      // erneut die reboot-Routine
      if((input.ctrl() == true) && (input.alt() == true) && (input.scancode()
                                                             == 0x53)){
         this -> reboot();
      }
      else{ // muss es ein Zeichen sein.... wahrscheinlich
         zeichen = input.ascii();
         if(zeichen){
            if(this -> zeichen != 0){ // ist bereits ein Zeichen im Puffer
               return false;
            }
            this -> key = input;
            return true; // um epilog anzufordern
         } else{
            return false;
         }
      }
   }
   return false;
}

void Keyboard::epilog(){
    // Wenn Tastaturbuffer voll,
    if(this -> add(this -> key)){
        // dann nicht noch weiter füllen und error ausgeben, sonst
        kout.setpos(0,5);
        kout << "Aufgabe 6 gerade in Arbeit, sorry";
        kout.flush();
    } else{
        // Semaphore erhöhen
        this -> semaphore.Semaphore::v();
        // buffer zurücksetzen; genau wie vorher
        this -> key.ascii(0);
    }
}

Key Keyboard::getKey(){
    // blockieren, bis key gedrück wurde und zurückgegeben werden kann
    this -> semaphore.p();
    // key ausgeben und aus dem buffer löschen
    return this -> remove();
}

bool Keyboard::add(Key zeichen){
    // wenn aktueller buffer kleiner als maximum,
    if(this -> limit < BUF_LEN){
        // dann neuen key anfügen
        this -> buffer[this -> tail] = zeichen;
        // tail um eins erhöhen.
        // falls tail > BUF_LEN durch modulo von vorne anfangen
        this -> tail = (tail++) % BUF_LEN;
        // aktuellen buffer um 1 erhöhen
        this -> limit++;
        // return true, wenn zeichen angehängt werden konnte
        return true;
    }
    // return false, wenn nicht
    return false;
}

Key Keyboard::remove(){
    // Hilfsvariable
    Key help;
    // hole erstes Element aus dem Buffer
    help = this -> buffer[head];
    // erniedrige aktuellen buffer um eins, da gleich ein Element gelöscht wird
    this -> limit--;
    // gleiches Procedere, wie in add()
    this -> head = (this -> head++) % BUF_LEN;
    // gib alten head zurück
    return help;
}