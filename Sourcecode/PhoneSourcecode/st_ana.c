#include "header.h"
#include <stdio.h>

extern MEM data[USERNUM];

ST_ANA st_ana(int device, int event) {
    /* device: あるイベントを行う端末番号 */

    int state = data[device].state;
    int i;
    
    ST_ANA result = {0, 0};

    /* deviceの状態による分岐 */
    switch (state) {
        case idle:
            /*入力されたイベントによる分岐*/
            if (event == offhook) {
                result.anal = OR_ANA_FUNC;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;

        case dialtone:
            if (event == onhook) {
                result.task = TASK10;

            }else if (event == dial) {
                result.anal = NUM_ANA_FUNC;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;

        case ringing:
            if (event == offhook && data[device].or_ter_ident == terminate) {
                result.task = TASK23;
                
            }else if (event == onhook && data[device].or_ter_ident == originate) {
                result.task = TASK20;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;

        case talk:
            if (event == onhook) {
                result.task = TASK30;

            }else if(event == group){
                result.task = TASK37;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;

        case busy:
            if (event == onhook) {
                result.task = TASK40;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;

        case pass_input:
            if(event == dial){
                result.anal = PASS_ANA_FUNC;

            }else if(event == onhook){
                result.task = TASK50;

            }else{
                printf("pass_input, イベント（%d）は無効です\n", event);
            }
            break;
        
        case talk_group:
            if(event == onhook){
                result.task = TASK60;

            }else if(event == group){
                result.anal = GROUP_ANA_FUNC;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;
        
        case pass_set:
            if(event == dial){
                result.task = TASK76;

            }else if(event == onhook){
                result.task = TASK70;

            }else{
                printf("イベント（%d）は無効です\n", event);
            }
            break;

        default:
            /* 条件に一致しない場合は何もしない */
            break;
    }

    return result;
}

