/**********************************************************************************************************************/
/* Author:      P. Luettmann, J. Telljohann                                                                           */
/* Version:     2.0                                                                                                   */
/* License:     none                                                                                                  */
/**********************************************************************************************************************/


#include "user/appl.h"
#include "machine/plugbox.h"
#include "device/cgastr.h"
#include "guard/guard.h"
#include "machine/pic.h"
#include "syscall/guarded_scheduler.h"
#include "user/loop.h"
#include "device/keyboard.h"
#include "device/watch.h"

#define STACK_SIZE 1024


CGA_Stream kout;            // Ausgabeobjekt
Plugbox plugbox;            // Plugbox :D
Guard guard;                // Guess what
Guarded_Scheduler scheduler;        // Scheduler
PIC pic;                    // programmable interrupt controler
CPU cpu;

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

    Watch watch(5000);

    Application appl(stack1+STACK_SIZE);
    Loop loop1(stack2+STACK_SIZE);

    appl.killLoop1(&loop1);

    guard.enter();

    scheduler.ready(appl);
    scheduler.ready(loop1);

    watch.windup();

    cpu.enable_int();

    scheduler.schedule();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
