#include "header.h"
#include <stdio.h>

extern MEM data[USERNUM];

void next_state(NMEM* address){
    int i;
    
    for(i = 0; i < 3; i++){/* 相手端末の書き換えを可能にするため */
        if(address[i].flag == 1){
            data[address[i].ln].state = address[i].state;
            address[i].flag = 0;
        }
    }
}
