//
// Created by anonymous on 31.01.19.
//

#include "writer.h"

void Writer::action() {
    int x = 0; int y = 3;
    waiter.wait();
    kout.setpos(x,y);
    kout << keyboard.getKey().ascii();
    kout.flush();
    waiter.signal();
    while (true){
        Key key = keyboard.getKey();
        waiter.wait();
        kout.setpos(x,y);
        if(key.ascii() != 8){
            kout << key.ascii();
            kout.flush();
        } else{
            kout.setpos(--x,y);
            if(x >= 0){
                kout << " ";
                kout.setpos(x,y);
            }else{
                kout.setpos(79, --y);
            }
            if(y < 4){
                kout.setpos(0,4);
            }
        }
        kout.getpos(x,y);
        waiter.signal();
    }
}