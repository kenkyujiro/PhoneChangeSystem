#include "header.h"
#include <stdio.h>

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task23(int device, NMEM* address){
    /* device: 着端末番号 */

    int i;
    int other = data2[device].terminal[0];

    output(disconnect,other,RINGBACKTONE);
    output(disconnect,device,RINGINGTONE);
    output(connect,other,device);

    if(address != NULL){
        /* 端末の状態書き換え */
        address[0].flag = 1;
        address[0].ln = device;
        address[0].state = talk;

        /* 相手端末の状態書き換え */
        address[1].flag = 1;
        address[1].ln = other;
        address[1].state = talk;
    }
    else{
        printf("そのアドレスは無効です！！\n");
    }
}
