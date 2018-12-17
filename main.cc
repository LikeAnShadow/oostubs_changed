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
#include "thread/scheduler.h"
#include "user/loop.h"
#include "device/keyboard.h"


#define STACK_SIZE 1024


CGA_Stream kout;            // Ausgabeobjekt
Plugbox plugbox;            // Plugbox :D
Guard guard;                // Guess what
Scheduler scheduler;        // Scheduler
PIC pic;                    // programmable interrupt controler

unsigned char stack1[STACK_SIZE];
unsigned char stack2[STACK_SIZE];
unsigned char stack3[STACK_SIZE];

int main()
{
    Keyboard keyboard;
    keyboard.plugin();

    kout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    kout.flush();

    Application appl(stack1+STACK_SIZE);
    Loop loop1(stack2+STACK_SIZE, 'a');
    Loop loop2(stack3+STACK_SIZE, 'b');

    appl.killLoop1(&loop1);

    scheduler.ready(appl);
    scheduler.ready(loop1);
    scheduler.ready(loop2);
    scheduler.schedule();

    // Ein Betriebssystem sollte eben nicht plötzlich enden (^.^)
    while(1);
}
