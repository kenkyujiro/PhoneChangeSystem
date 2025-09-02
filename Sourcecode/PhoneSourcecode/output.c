#include "header.h"
#include <stdio.h>

void output(int request, int parameter1, int parameter2){
    /* 接続の場合 */
    if(request == connect){
        switch(parameter2){
            case SR:
                printf("[%d]=>数字受信装置接続\n",parameter1);
                break;

            case RINGINGTONE:
                printf("[%d]=>呼出し音送出\n",parameter1);
                break;

            case RINGBACKTONE:
                printf("[%d]=>呼び返し音送出\n",parameter1);
                break;

            case BUSYTONE:
                printf("[%d]=>ビジー音送出\n",parameter1);
                break;

            case DIALTONE:
                printf("[%d]=>ダイヤルトーン送出\n",parameter1);
                break;

            case PASSTONE:
                printf("[%d]=>パストーン送出\n",parameter1);
                break;

            case GROUP:
                printf("[%d]=>グループ通話接続\n",parameter1);
                break;

            default:
                printf("[%d]と[%d]=>接続\n",parameter1, parameter2);
                break;
        }
    /* 切断の場合 */
    }else{
        switch(parameter2){
            case SR:
                printf("[%d]=>数字受信装置切断\n",parameter1);
                break;

            case RINGINGTONE:
                printf("[%d]=>呼出し音切断\n",parameter1);
                break;

            case RINGBACKTONE:
                printf("[%d]=>呼び返し音切断\n",parameter1);
                break;

            case BUSYTONE:
                printf("[%d]=>ビジー音切断\n",parameter1);
                break;

            case DIALTONE:
                printf("[%d]=>ダイヤルトーン切断\n",parameter1);
                break;

            case PASSTONE:
                printf("[%d]=>パストーン切断\n",parameter1);
                break;

            case GROUP:
                printf("[%d]=>グループ通話切断\n",parameter1);
                break;

            default:
                printf("[%d]と[%d]=>切断\n",parameter1, parameter2);
                break;
        }
    }
}


