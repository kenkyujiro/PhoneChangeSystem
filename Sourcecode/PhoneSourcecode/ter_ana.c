#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern MEM data[USERNUM];

TER_ANA	ter_ana(int num){
    /* num: 着端末番号 */

    TER_ANA result = {0, 0};
    
    if(data[num].state == idle){
        result.task = TASK12;

    }else if(data[num].state == talk_group){
        result.task = TASK15;
        
    }else{
        result.task = TASK14;
    }

    return result;
}