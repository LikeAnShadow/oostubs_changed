/**********************************************************************************************************************/
/* Author:      P. Luettmann, J. Telljohann                                                                           */
/* Version:     2.0                                                                                                   */
/* License:     none                                                                                                  */
/**********************************************************************************************************************/


#include "user/appl.h"
#include "user/loop.h"

#include "machine/plugbox.h"
#include "machine/pic.h"

#include "device/cgastr.h"
#include "device/keyboard.h"
#include "device/watch.h"

#include "guard/guard.h"

#include "syscall/guarded_organizer.h"
#include "syscall/guarded_buzzer.h"

#include "meeting/bellringer.h"

#define STACK_SIZE 1024

Keyboard keyboard;
CGA_Stream kout;
Plugbox plugbox;
Guard guard;
PIC pic;
CPU cpu;
Guarded_Organizer guarded_organizer;
Bellringer bellringer;

unsigned char stack1[STACK_SIZE];
unsigned char stack2[STACK_SIZE];

int main()
{

    kout.setpos(0,0);
    for(int i = 0; i < 25; i++){
        for(int j = 0; j< 80; j++){
            kout.print(" ", 1);
        }
    }

    Watch watch(1000); // 1 ms

    Application appl(stack1+STACK_SIZE);
    Loop loop1(stack2+STACK_SIZE);

    guard.enter();

    guarded_organizer.ready(appl);
    guarded_organizer.ready(loop1);

    watch.windup();
    keyboard.plugin();

    cpu.enable_int();

    guarded_organizer.schedule();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
