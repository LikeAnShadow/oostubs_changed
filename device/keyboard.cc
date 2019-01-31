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

Keyboard::Keyboard() : semaphore(0) {}

static Keyboard_Controller kb;

void Keyboard::plugin(){
   plugbox.assign(plugbox.keyboard, *this); // melde keyboard an
   pic.allow(PIC::devices::keyboard); // erlaube unterbrechungen von keyboard
}

bool Keyboard::prolog(char* msg){
   /*char zeichen;
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
   return false;*/
   Key key = kb.key_hit();
   if(key.valid()){
       this -> buffer = key;
       unsigned char c = key.ascii();

       if(c == 32 && key.ctrl() && key.alt()){
           kb.reboot(); //strg-alt-entf zum reboot
       }
       if (key.scancode() == 83 && key.ctrl() && key.alt()) {
           kb.reboot(); //strg-alt-entf zum reboot
       }
       return true;
   } else{
       return false;
   }
}

void Keyboard::epilog(){
    /*// Wenn Tastaturbuffer voll,
    if(this -> add(this -> key)){
        kout.setpos(x,y);
        kout << this -> key.ascii();
        kout.flush();
        kout.getpos(x,y);
    } else{
        // Semaphore erhöhen
        this -> semaphore.Semaphore::signal();
        // buffer zurücksetzen; genau wie vorher
        this -> key.ascii(0);
    }*/
    Key key = this -> buffer;
    if(key.ascii() != 0){
        semaphore.Semaphore::v();
    }

}

Key Keyboard::getKey(){
    // blockieren, bis key gedrück wurde und zurückgegeben werden kann
    this -> semaphore.p();
    // key ausgeben und aus dem buffer löschen
    return this -> buffer;
}
