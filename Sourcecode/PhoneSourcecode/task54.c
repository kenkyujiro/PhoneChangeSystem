#include "header.h"
#include <stdio.h>  

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

/* task54で、配列の中の0を右に寄せる関数 */
void shift_zeros_right_t54(int *array, int size) {
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

void task54(int device, NMEM* address){
    /* device: 発端末番号 */

    int i, j;

    int other = data2[device].terminal[0];

    output(disconnect,device,DIALTONE);
    output(connect,device,BUSYTONE);

    /* 端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = busy;

    /* 自分の番号を着端末の 'terminal' 配列から見つける */
    for(i=1;i<USERNUM; i++){
        for (int j = 0; j < USERNUM; j++) {
            if(i == device){
                data2[i].terminal[j] = 0; /* 全要素を初期化 */

            }else{
                if(data2[i].terminal[j] == device){
                    data2[i].terminal[j] = 0;

                }else if(data2[i].terminal[j] == 0){
                    break;
                }
            }
        }
        // 0を右に寄せる //
        shift_zeros_right_t54(data2[i].terminal, USERNUM);
    }

}