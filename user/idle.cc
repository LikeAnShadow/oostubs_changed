//
// Created by anonymous on 31.01.19.
//

#include "idle.h"

void Idle::action(){
    while (true){
        cpu.idle();
    }
}
