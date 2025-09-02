#include "header.h"
#include <stdio.h>  

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task63(int device, NMEM* address){
    /* device: イベント:group を行う端末番号*/

    int other = data2[device].terminal[0];

    output(disconnect,device, GROUP);
    output(disconnect,other, GROUP);

    /* 端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = talk;

    /* 相手端末の状態書き換え */
    address[1].flag = 1;
    address[1].ln = other;
    address[1].state = talk;
}