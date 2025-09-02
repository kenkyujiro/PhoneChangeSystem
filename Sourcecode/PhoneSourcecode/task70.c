#include "header.h"
#include <stdio.h>  
 
extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task70(int device,NMEM* address){
    /* device: イベント: onhookを行う端末番号*/

    int other = data2[device].terminal[0];

    output(disconnect,device,PASSTONE);
    output(disconnect,other,PASSTONE);
    output(connect,other,BUSYTONE);

    if(address != NULL){
        /* 端末の状態書き換え */
        address[0].flag = 1;
        address[0].ln = device;
        address[0].state = idle;

        /* 相手端末の状態書き換え */
        address[1].flag = 1;
        address[1].ln = other;
        address[1].state = busy;

        /* 発着識別子の書き換え */
        if(data[device].or_ter_ident==originate){
            data[device].or_ter_ident=terminate;
        }

        if(data[other].or_ter_ident==originate){
            data[other].or_ter_ident=terminate;
        }

    }else{
        printf("そのアドレスは無効です！！\n");
    }



}