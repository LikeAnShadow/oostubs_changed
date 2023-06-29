//
// Created by anonymous on 31.01.19.
//

#define BACKSPACE 8
#define ENTER 13
#include "shell.h"
#include "strcmp.h"
#include "shellcommands.h"
#include "apps.h"

void Shell::action() {
    waiter.wait();
    kout.getpos(x,y);
    waiter.signal();
    while (true){
        if(printShell) {
            kout << "Shell> ";
            kout.flush();
            kout.setpos(x+7,y);
            kout.getpos(x,y);
            printShell = false;
        }
            Key key = keyboard.getKey();
            waiter.wait();
            kout.setpos(x,y);
        if(bufferpos < BUFFERSIZE - 1){
            switch (key.ascii())
            {
            case BACKSPACE:
                if(bufferpos != 0){
                    kout.setpos(--x,y);
                    kout << " ";
                    kout.flush();
                    kout.setpos(x,y);
                    --bufferpos;
                }else{
                    if(bufferpos != 0) {
                        kout.setpos(79, --y);
                        --bufferpos;
                    }
                }
                if(y < 5){
                    kout.setpos(0,5);
                }
                break;
            case '\n':
                buffer[bufferpos] = '\0';
                kout.flush();
                commandParser(buffer);
                break;
            default:
                kout << key.ascii();
                buffer[bufferpos] = key.ascii();
                ++bufferpos;
                kout.flush();
                break;
            }
    } else if(key.ascii()=='\n'){
            buffer[bufferpos] = '\0';
            kout.flush();
            commandParser(buffer);
    }
    kout.getpos(x,y);
    waiter.signal();
}
}

void Shell::commandParser(char* buffer){
    printShell = true;
    kout.setpos(0,++y);
    kout.getpos(x,y);
    if (bufferpos == 0) {}
    else if(HELP) {
        kout << "help - Zeigt diese Hilfe an" << endl;
        kout << "reboot - Startet das System neu" << endl;
        kout << "shutdown - Faehrt das System herunter" << endl;
        kout.flush();
    }
    else if(REBOOT) {
        kout << "Rebooting..." << endl;
        kout.flush();
        keyboard.reboot();
    }
    else if(SHUTDOWN) {
        kout << "Power off..." << endl;
        kout.flush();
        keyboard.shutdown();
    } 
    else if(MULTAPP) {    
        
    }
    else {
        kout << "Diese Eingabe ist ungueltig!" << endl;
        kout.flush();
    }
    for(int i = bufferpos; i>-1;--i) {
        buffer[i] = 0;
    }
    bufferpos = 0;
}