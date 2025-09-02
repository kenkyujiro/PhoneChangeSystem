#include "header.h"
#include <stdio.h>  

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task56(int device, NMEM* address){
    /* device: 発端末番号 */

    int other = data2[device].terminal[0];

    output(disconnect,device,PASSTONE);
    output(connect,device,GROUP);
    
    /* 端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = talk_group;

    /* 相手端末のパスワードを共有する */
    data[device].password = data[other].password;

    
}