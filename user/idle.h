//
// Created by anonymous on 31.01.19.
//

#ifndef __idle_include__
#define __idle_include__

#include "syscall/thread.h"
#include "machine/cpu.h"

extern CPU cpu;


class Idle : public Thread{

private:
    Idle(const Idle &copy); // Verhindere Kopieren

public:
    Idle() : Thread(){

    }

    void action();
};

#endif
