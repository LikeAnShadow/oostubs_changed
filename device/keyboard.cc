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

Keyboard::Keyboard() : Gate(), Keyboard_Controller() {}

void Keyboard::plugin(){
   // Erstelle pic object
   PIC pic;

   plugbox.assign(plugbox.keyboard, *this); // melde keyboard an
   pic.allow(keyboard); // erlaube unterbrechungen von keyboard

   return;
}

void Keyboard::trigger(){
   char zeichen;
   Key input;
   int xpos, ypos;

   input = this->key_hit();

   do{
      // endlich eine Möglichkeit ein reboot abzufangen. Hier mit strg-alt-entf
      if(input.ctrl() == true && input.alt() == true && input.scancode() ==
      0x53){
         this -> reboot(); //0x53 steht für entf-Taste
      }
      else{
         zeichen = input.ascii();
         if(zeichen){
            kout.getpos(xpos, ypos);
            kout.setpos(xpos, ypos);
            if(zeichen == '\b'){
               if(--xpos < 0){
                  kout.setpos(80, --ypos);
               }
               kout.setpos(xpos, ypos);
               kout.print(" ", 1);
               kout.setpos(xpos, ypos);
            }else{
               if(++xpos >= 80){
                  xpos = 0;
                  ypos++;
               }

               kout.print(&zeichen, 1);
            }
         }
         input = this -> key_hit();
      }
   }while (input.valid());
}