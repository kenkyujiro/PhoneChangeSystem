#include "header.h"
#include <stdio.h>
#include <stdlib.h>

extern MEM data[USERNUM];

void tk_select(int device,int event,int telnum){   
    int i;
    int info;

    ST_ANA result_st = {0, 0};
    NUM_ANA result_num = {0, 0, 0};
    OR_ANA result_or = {0, 0};
    TER_ANA result_ter = {0, 0};
    PASS_ANA result_pass = {0, 0};
    GROUP_ANA result_group = {0, 0};

    NMEM* address[3];

    /* address 配列のメモリを動的に確保 */
    for (i = 0; i < 3; i++) {
        address[i] = malloc(sizeof(NMEM));  /* NMEM 型のメモリ領域を確保 */
        if (address[i] == NULL) {  /* メモリ確保に失敗した場合のエラーチェック */
            printf("Error: Memory allocation failed for address[%d].\n", i);
            return;  /* メモリ確保失敗時には処理を中断 */
        }
    }

    /* ST_ANA の結果を取得する */
    result_st =	st_ana(device,event);

    /* ST_ANA の結果に基づいて次の分析を行う */
    switch(result_st.anal){
        case NUM_ANA_FUNC:
            result_num = num_ana(telnum);
            break;

        case OR_ANA_FUNC:
            result_or = or_ana(device);
            break;

        case PASS_ANA_FUNC:
            result_pass = pass_ana(telnum);
            break;
        
        case GROUP_ANA_FUNC:
            result_group = group_ana(device);
            break;

        default:
            /* 条件に一致しない場合は何もしない */
            break;
    }

    info = result_num.info; /* NUM_ANA の結果を info に格納 */

    /* NUM_ANA の結果が TER_ANA_FUNC であれば、次に TER_ANA を行う */
    if(result_num.anal == TER_ANA_FUNC){
        result_ter = ter_ana(info);
    }

    /* ST_ANAで決定したタスクの実行 */
    switch(result_st.task){
        case TASK10:
            task10(device,address[0]);
            break;

        case TASK23:
            task23(device,address[0]);
            break;

        case TASK20:
            task20(device,address[0]);
            break;

        case TASK30:
            task30(device,address[0]);
            break;

        case TASK37:
            task37(device, address[0]);
            break;

        case TASK40:
            task40(device,address[0]);
            break;

        case TASK50:
            task50(device,address[0]);
            break;
        
        case TASK60:
            task60(device,address[0]);
            break;
        
        case TASK70:
            task70(device,address[0]);
            break;

        case TASK76:
            task76(device,telnum,address[0]);
            break;

        default:
            /* 条件に一致しない場合は何もしない */
            break;
    }

    /* OR_ANAで決定したタスクの実行 */
    switch(result_or.task){
        case TASK01:
            task01(device,address[0]);
            break;

        case TASK04:
            task04(device,address[0]);
            break;
        
        default:
            /* 条件に一致しない場合は何もしない */
            break;
    }
    
    /* NUM_ANA、TER_ANAで決定したタスクの実行 */
    switch(result_ter.task){
        case TASK12:
            task12(device,info,address[0]);
            break;
        
        case TASK15:
            task15(device,info,address[0]);
            break;
        
        default:
            /* 条件に一致しない場合は何もしない */
            break;
    }

        /* TASK14 を実行する条件は２つある */
    if(result_ter.task == TASK14 || result_num.task == TASK14){
        task14(device,address[0]);
    }

    /* PASS_ANAで決定したタスクの実行 */
    switch(result_pass.task){
        case TASK56:
            task56(device,address[0]);
            break;
        
        case TASK54:
            task54(device,address[0]);
            break;
        
        default:
            /* 条件に一致しない場合は何もしない */
            break;
    }

    /* GROUP_ANAで決定したタスクの実行 */
    if(result_group.task == TASK63){
        task63(device,address[0]);
    }

    /* 次状態へ書き換え */
    next_state(address[0]);

    /* 動的メモリの解放 */
    for (i = 0; i < 3; i++) {
        free(address[i]);  /* 確保したメモリを解放 */
    }
}