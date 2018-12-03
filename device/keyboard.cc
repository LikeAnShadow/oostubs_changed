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

Keyboard::Keyboard() : Gate(), Keyboard_Controller(), zeichen(0) {}

void Keyboard::plugin(){
   plugbox.assign(plugbox.keyboard, *this); // melde keyboard an
   pic.allow(PIC::devices::keyboard); // erlaube unterbrechungen von keyboard

   return;
}

/*
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
               char *read;
               read = (char *)0xb8000 + 2 *(xpos + ypos * 80)-2;
               if(*read == ' '){
                  while(*read == ' '){
                     --xpos;
                     read = (char *)0xb8000 + 2 *(xpos + ypos * 80);
                  }
                  xpos+= 2;
               }
               kout.setpos(--xpos, ypos);
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
*/

bool Keyboard::prolog(){
   char zeichen;
   Key input;

   input = this -> key_hit();

   do{
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
            this -> zeichen = zeichen;
            return true; // um epilog anzufordern
         }
      }

   }while(input.valid()); // weitere Zeichen abfragen, wenn vorhanden

   return false;
}

void Keyboard::epilog(){
   int xpos, ypos;
   kout.getpos(xpos, ypos);
   kout.setpos(xpos, ypos);
   if(zeichen == '\b'){
      char *read;
      read = (char *)0xb8000 + 2 *(xpos + ypos * 80)-2;
      if(*read == ' '){
         while(*read == ' '){
            --xpos;
            read = (char *)0xb8000 + 2 *(xpos + ypos * 80);
         }
         xpos+= 2;
      }
      kout.setpos(--xpos, ypos);
      kout.print(" ", 1);
      kout.setpos(xpos, ypos);
   }else{
      if(++xpos >= 80){
         xpos = 0;
         ypos++;
      }

      kout.print(&zeichen, 1);
      zeichen = 0;
   }
}