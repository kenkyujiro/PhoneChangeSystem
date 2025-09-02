#include "header.h"
#include <stdbool.h>
#include <stdio.h>

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

GROUP_ANA group_ana(int device){
    /* device: グループ通話中のイベントを行う端末番号 */
    
    GROUP_ANA result = {0,0};

    if(data2[device].terminal[1] != 0){
        printf("イベント3は無効です\n");

    }else if(data2[device].terminal[1] == 0){
        result.task = TASK63;
    }

    return result;
}