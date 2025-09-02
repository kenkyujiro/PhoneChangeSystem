#include "header.h"
#include <stdio.h>  
 
void task04(int num,NMEM* address){
    /* num: 発端末番号 */
    output(connect,num,BUSYTONE);

    /* 端末の状態書き換え */
    address->flag = 1;
    address->ln = num;
    address->state = busy;
}
