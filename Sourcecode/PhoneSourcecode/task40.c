#include "header.h"
#include <stdio.h>  

extern MEM data[USERNUM];

void task40(int device, NMEM* address){
    /* device: 発端末番号 */

    output(disconnect,device,BUSYTONE);

    /* 端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = idle;
}