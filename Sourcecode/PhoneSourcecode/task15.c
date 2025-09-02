#include "header.h"
#include <stdio.h>  

extern MEM data[USERNUM];
extern MEM2 data2[USERNUM];

void task15(int device,int device_tel, NMEM* address){
    /* device: 発端末番号, device_tel: 着端末番号 */

    int i, j;

    /* 配列の要素数をカウント */
    int count = 0;

    /* 相手端末番号を格納する配列 */
    int others[USERNUM];

    /* 上記配列のインデックスを表す */
    int index = 0;

    output(disconnect, device, DIALTONE);
    output(connect, device, PASSTONE);

    /* 発端末の状態書き換え */
    address[0].flag = 1;
    address[0].ln = device;
    address[0].state = pass_input;

    others[index] = device_tel;

    index = 1;

    /* 相手が現在何人と接続しているかを取得する */
    for(i = 0; i < USERNUM; i++){
        if(data2[device_tel].terminal[i] != 0){
            if (index < USERNUM) {  /* 配列の境界をチェック */
                others[index] = data2[device_tel].terminal[i];
                index++;
                count++;
            } else {
                break;
            }
        }else{
            break;
        }
    }

    /* 'others' 配列を 'data[device].terminal' にコピー */
    for (i = 0; i < USERNUM; i++) {
        data2[device].terminal[i] = (i < index) ? others[i] : 0;
    }

    /* others配列に格納されている端末番号のterminalに番号を追加 */
    for(i = 0; i <= count; i++){
        for(j = 0; j < USERNUM; j++){
            if(data2[others[i]].terminal[j] == 0){
                data2[others[i]].terminal[j] = device;
                break;
            }
        }
    }
}