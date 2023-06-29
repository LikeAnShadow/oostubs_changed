//
// Created by anonymous on 31.01.19.
//

#ifndef OOSTUBS_SHELL_H
#define OOSTUBS_SHELL_H

#define BUFFERSIZE 2048

#include "user/externs.h"
#include "syscall/guarded_keyboard.h"
#include "machine/key.h"
#include "syscall/guarded_semaphore.h"
#include "object/strbuf.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Keyboard keyboard;
extern Guarded_Semaphore waiter;
extern Guarded_Organizer guarded_organizer;

class Shell : public Thread{
private:
    Shell(const Shell &copy);
    void commandParser(char* buffer);
    char buffer[BUFFERSIZE];
    int bufferpos = 0;
    int x;int y;
    bool printShell = true;

public:
    Shell() : Thread(){}

    void action();
};


#endif //OOSTUBS_WRITER_H
