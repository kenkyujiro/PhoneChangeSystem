#include "header.h"
#include <stdbool.h>
#include <stdio.h>

extern MEM data[USERNUM];

NUM_ANA num_ana(int num){
    int i;

    /* true:端末番号を発見, false:端末番号が未発見 */
    bool is_find = false;

    NUM_ANA result = {0,0,0};


    for(i = 1; i < USERNUM; i++){
        if(data[i].telnum == num){
            result.anal = TER_ANA_FUNC;
            result.info = i;
            is_find = true;
            break;
        }
    }

    if(is_find == false){
        printf("誤ったダイアルです\n");
        result.task = TASK14;
    }

    return result;
}