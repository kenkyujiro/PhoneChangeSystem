#include "header.h"
#include <stdio.h>

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task76(int device, int password, NMEM* address){
    /* device: イベント:dial を行う端末番号*/

    int other = data2[device].terminal[0];

    output(disconnect,device,PASSTONE);
    output(disconnect,other,PASSTONE);
    output(connect,device,GROUP);
    output(connect,other,GROUP);

    /* 設定したパスワードを相手端末と共有する*/
    data[device].password = password;
    data[other].password = data[device].password;

    if(address != NULL){
        // 着端末の状態書き換え //
        address[0].flag = 1;
        address[0].ln = device;
        address[0].state = talk_group;

        // 相手端末の状態書き換え //
        address[1].flag = 1;
        address[1].ln = other;
        address[1].state = talk_group;

    }else{
        printf("そのアドレスは無効です！！\n");
    }
}