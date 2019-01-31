//
// Created by anonymous on 31.01.19.
//

#ifndef OOSTUBS_WRITER_H
#define OOSTUBS_WRITER_H

#include "user/externs.h"
#include "syscall/guarded_keyboard.h"
#include "machine/key.h"
#include "syscall/guarded_semaphore.h"

extern Guarded_Keyboard keyboard;
extern Guarded_Semaphore waiter;

class Writer : public Thread{
private:
    Writer(const Writer &copy);

public:
    Writer(void *tos) : Thread(tos){}

    void action();
};


#endif //OOSTUBS_WRITER_H
