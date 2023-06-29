#include "mult.h"

void Mult::action() {
    waiter.wait();
    kout.getpos(x,y);
    i = 1;
    waiter.signal();
      while (true){
        waiter.wait();
        kout << i;
        kout.flush();
        i = i*2;
        waiter.signal();
    }

}