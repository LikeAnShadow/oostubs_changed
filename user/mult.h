//
// Created by anonymous on 31.01.19.
//

#ifndef OOSTUBS_MULT_H
#define OOSTUBS_MULT_H

#include "user/externs.h"
#include "syscall/guarded_keyboard.h"
#include "machine/key.h"
#include "syscall/guarded_semaphore.h"

extern Guarded_Keyboard keyboard;
extern Guarded_Semaphore waiter;

class Mult : public Thread{
private:
    Mult(const Mult &copy);
    int x,y;
    int i;

public:
    Mult() : Thread(){}

    void action();
};


#endif //OOSTUBS_MULT_H