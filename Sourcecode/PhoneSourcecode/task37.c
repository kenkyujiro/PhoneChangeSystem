#include "header.h"
#include <stdio.h>

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task37(int device, NMEM* address){
    /* device: イベント:group を行う端末番号 */

    int other = data2[device].terminal[0];

    output(disconnect, device, other);
    output(connect,device,PASSTONE);
    output(connect,other,PASSTONE);

    if(address != NULL){
        /* 端末の状態書き換え */
        address[0].flag = 1;
        address[0].ln = device;
        address[0].state = pass_set;

        /* 相手端末の状態書き換え */
        address[1].flag = 1;
        address[1].ln = other;
        address[1].state = pass_set;
        
    }else{
        printf("そのアドレスは無効です！！\n");
    }
}