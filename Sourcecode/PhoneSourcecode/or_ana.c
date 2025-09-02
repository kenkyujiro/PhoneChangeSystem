#include "header.h"
#include <stdio.h>

extern MEM data[USERNUM];

OR_ANA	or_ana(int device){
    /* device: 発信許可を判別する端末番号*/
    
    OR_ANA result = {0,0};

    if(data[device].or_ac == YES){
        result.task = TASK01;

    }else{
        result.task = TASK04;
    }

    return result;

}