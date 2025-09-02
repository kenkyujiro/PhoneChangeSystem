#include "header.h"
#include <stdio.h>  

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

/* task60で、配列の中の0を右に寄せる関数 */
void shift_zeros_right_t60(int *array, int size) {
    int index = 0; /* ゼロ以外の要素を配置する位置 */

    /* ゼロ以外の要素を前に詰める */
    for (int i = 0; i < size; i++) {
        if (array[i] != 0) {
            array[index++] = array[i];
        }
    }

    /* 残りの部分をゼロで埋める */
    while (index < size) {
        array[index++] = 0;
    }
}

/* グループ通話から抜ける際のタスク */
void task60(int device, NMEM* address){
    /* device: グループ通話から抜ける端末番号 */

    int i, j;
    int other = data2[device].terminal[0];

    output(disconnect,device, GROUP);

    /* 自分の番号を通話中の 'terminal' 配列から見つける */
    for(i=1;i<USERNUM; i++){
        for (int j = 0; j < USERNUM; j++) {
            if(i == device){
                data2[i].terminal[j] = 0; /* 全要素を初期化 */

            }else{
                if(data2[i].terminal[j] == device){
                    output(disconnect,device, i);
                    data2[i].terminal[j] = 0;

                }else if(data2[i].terminal[j] == 0){
                    break;
                }
            }
        }
        // 0を右に寄せる //
        shift_zeros_right_t60(data2[i].terminal, USERNUM);
    }

    /* 端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = idle;

    /* 発着識別子の書き換え */
    if(data[device].or_ter_ident==originate){
        data[device].or_ter_ident=terminate;
    }

    /* パスワードの初期化 */
    data[device].password = -1;

    /* グループ通話が二人の場合, 相手端末情報の書き換え */
    if(data2[other].terminal[0] == 0){
        output(disconnect,other, GROUP);
        output(connect,other, BUSYTONE);

        address[1].flag = 1;
        address[1].ln = other;
        address[1].state = busy;
        
        if(data[other].or_ter_ident == originate){
            data[other].or_ter_ident=terminate;
        }

        /* なぜか発信拒否になることがあるため、その場合の対処 */
        if(data[other].or_ac == NO){
            data[other].or_ac = YES;
        }
        
        data[other].password = -1;
    }

}