#include "header.h"
#include <stdio.h> 
#include <stdbool.h> 

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];
 
void task12(int device,int device_tel, NMEM* address){
    /* device: 発端末番号, device_tel: 着端末番号 */
    int i;

    bool is_break_device = false;
    bool is_break_other = false;

   
    output(disconnect,device,SR);
    output(disconnect,device,DIALTONE);

    output(connect,device,RINGBACKTONE);
    output(connect,device_tel,RINGINGTONE);

    /* 発端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = ringing;

    /* 着端末の状態書き換え */
    address[1].flag = 1;
    address[1].ln = device_tel;
    address[1].state = ringing;

    /* 発着識別子の書き換え */
    data[device].or_ter_ident = originate;
    data[device_tel].or_ter_ident = terminate;
    
    /* 相手端末情報の書き換え */
    for(i = 0; i < USERNUM; i++){
        if(data2[device].terminal[i] == 0){
            data2[device].terminal[i] = device_tel;
            is_break_device = true;
        }

        if(data2[device_tel].terminal[i] == 0){
            data2[device_tel].terminal[i] = device;
            is_break_other = true;
        }

        if(is_break_device == true && is_break_other == true){
            break;
        }
    }
}