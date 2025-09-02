#include "header.h"
#include <stdbool.h>
#include <stdio.h>

extern MEM data[USERNUM];

PASS_ANA pass_ana(int pass){
    /* pass: イベント:dial により入力された番号 */

    int i;

    /* true: 一致するパスワードを発見, false: 一致するパスワードを未発見 */
    bool is_find = false;

    PASS_ANA result = {0,0};

    for(i = 1; i < USERNUM; i++){
        if(data[i].password == pass){
            result.task = TASK56;
            is_find = true;
            break;
        }
    }

    if(is_find == false){
        printf("誤ったパスワードです\n");
        result.task = TASK54;
    }

    return result;
}