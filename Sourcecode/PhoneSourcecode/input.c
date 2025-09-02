#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

MEM data[USERNUM];
MEM2 data2[USERNUM];

/* 状態名を対応する文字列で表示する関数 */
const char* get_state_name(int state) {
    switch (state) {
        case idle: return "idle";
        case dialtone: return "dialtone";
        case ringing: return "ringing";
        case talk: return "talk";
        case busy: return "busy";
        case pass_input: return "pass_input";
        case talk_group: return "talk_group";
        case pass_set: return "pass_set";
        default: return "unknown";
    }
}

/* 発着識別子を対応する文字列で表示する関数 */
const char* get_or_ter_name(int or_ter_ident) {
    switch (or_ter_ident) {
        case originate: return "originate";
        case terminate: return "terminate";
        default: return "terminate";
    }
}

int main(void){
    int i, j;

    /* 初期設定をするかどうか */
    int setup = -1;

    /* 発信を禁止する端末番号を格納 */
    int not_allow = -1;

    /* 状態を変更する端末番号を格納 */
    int device_num = -1;
    /* 変更先の状態番号を格納 */
    int state_num = -1;
    /* 状態talkに変更する際の相手端末番号を格納 */
    int other_num = -1;

    /* 確認する個別データ情報番号を格納*/
    int info_select = -1;

    /* 1: 他の状態を見る */
    int is_check = -1;
    /* true: breakする*/
    bool is_break = false;
    

    char input[10];

    /* 端末番号を格納 */
    int device = -1;
    /* イベント番号を格納 */
    int event = -1;
    /* 電話番号またはパスワードを格納 */
    int telnum = -1;

    /* 'data' 配列の初期化 */
    for(i = 1; i < USERNUM; i++){
        data[i].telnum = 4000+i;
        data[i].state = idle;
        data[i].or_ac = YES;
        data[i].or_ter_ident = 0;
        data[i].password = -1;
    }

    /* 'data2' 配列の初期化 */
    for(i=1;i<USERNUM;i++){
        for (int j = 0; j < USERNUM; j++) {
            data2[i].terminal[j] = 0; /* 全要素を初期化 */
        }
    }

    printf("■□■□設計演習C Ver.1.3 ■□■□\n");

    while(1){
        /* 再度無限ループに戻ってきた場合に初期化をしておく */
        setup = -1;
        not_allow = -1;
        device_num = -1;
        state_num = -1;
        other_num = -1;

        printf("初期設定変更を行いますか？発信許可設定=1, 状態変更=2, 設定しない=0 >");
        scanf("%d", &setup);

        /* 発信許可設定*/
        if(setup == 1){
            printf("発信を許可しない端末番号入力>");
            scanf("%d", &not_allow);

            if(not_allow >= 1 || not_allow < USERNUM){
                data[not_allow].or_ac = NO;
                printf("端末[%d]を発信不可にしました．\n", not_allow);
            }

        /* 状態変更設定 */
        }else if(setup == 2){
            printf("状態を変更する端末番号入力>");
            scanf("%d", &device_num);

            if(device_num < 1 || device_num > USERNUM ){
                printf("無効な端末番号\n");
                continue;
            }

            printf("変更する状態番号入力 idle=0, dialtone=1, ringing=2, talk=3, busy=4>");
            scanf("%d", &state_num);

            if(state_num < 0 || state_num > 4){
                printf("無効な番号\n");
                continue;
            }

            data[device_num].state = state_num;

            /* 状態:talk に変更する場合*/
            if(state_num == 3){
                printf("相手端末番号>");
                scanf("%d", &other_num);

                if((other_num < 1 || other_num > USERNUM) || other_num == device_num ){
                    printf("無効な端末番号\n");
                    continue;
                }

                data[other_num].state = state_num;
                data[device_num].or_ter_ident = originate;

                data2[device_num].terminal[0] = other_num;
                data2[other_num].terminal[0] = device_num;

                printf("端末%dを状態%sに変更しました\n", other_num, get_state_name(data[other_num].state));
                printf("端末%dを発着識別子%sに変更しました\n", device_num, get_or_ter_name(data[device_num].or_ter_ident));

            }
            printf("端末%dを状態%sに変更しました\n", device_num, get_state_name(data[device_num].state));

        }else if(setup == 0){
            break;

        }else{
            continue;
        }
    }
    
    while(1){
        /* 再度無限ループに戻ってきた場合に初期化をしておく */
        is_check = -1;
        is_break = false;
        info_select = -1;
        for(i = 10; i < 10; i++){
            input[i] = 0;
        }
        device = -1;
        event = -1;
        telnum = -1;

        printf("\n端末番号(1-%d)>", USERNUM-1);
        scanf("%s", input);

        if (strcmp(input, "i") == 0) {
            while(1){
                printf("\n個別データ情報");
                printf("\n状態(1),発信を拒否する端末(2),相手端末(3),発着識別子(4),設定されたパスワード(5), 確認しない(0)>");
                scanf("%d", &info_select);

                switch(info_select){
                    /* 状態情報を確認 */
                    case 1:
                        printf("Terminal  State");
                        printf("\n-------------------\n");
                        for(i = 1; i < USERNUM; i++){
                            printf("\t%d\t%s\n", i, get_state_name(data[i].state));
                        }
                        break;

                    /* 発信拒否情報を確認 */
                    case 2:
                        printf("Terminal  Accept Flag");
                        printf("\n-------------------\n");
                        for(i = 1; i < USERNUM; i++){
                            printf("\t%d\t%s\n", i, data[i].or_ac == YES ? "YES" : "NO");
                        }
                        break;

                    /* 相手端末情報を確認 */
                    case 3:
                        printf("Terminal  Remote");
                        printf("\n-------------------\n");
                        for (i = 1; i < USERNUM; i++) {
                            printf("\t%d\t", i);
                            for (int j = 0; j < USERNUM; j++) {
                                if(data2[i].terminal[j]!= 0){
                                    printf("%d ", data2[i].terminal[j]); /* 配列の要素を順に表示 */
                                }
                            }
                            printf("\n");
                        }
                        break;

                    /* 発着識別子を確認 */
                    case 4:
                        printf("Terminal   Orig. or Term.");
                        printf("\n-------------------\n");
                        for(i = 1; i < USERNUM; i++){
                            printf("\t%d\t%s\n", i, get_or_ter_name(data[i].or_ter_ident));
                        }
                        break;

                    /* パスワード情報を確認 */
                    case 5:
                        printf("Terminal   Password.");
                        printf("\n-------------------\n");
                        for(i = 1; i < USERNUM; i++){
                            printf("\t%d\t%d\n", i, data[i].password);
                        }
                        break;

                    case 0:
                        is_break = true;
                        break;

                    default:
                        printf("\n無効な選択です。\n");
                        continue;
                }

                /* 他の情報を確認するかどうか */
                if(is_break == false){
                    while(1){
                        printf("\n他の情報も見ますか？ Yes=1 No=0 >");
                        scanf("%d", &is_check);
                        if(is_check == 0){
                            is_break = true;
                            break;

                        }else if(is_check == 1){
                            is_break = false;
                            break;

                        }else{
                            continue;
                        }
                    }
                }
                
                /* 他の情報を確認しないなら、個別データ情報表示を終了 */
                if(is_break == true){
                    break;
                }
            }
            continue;

        }else{
            /* inputの型をint型に変更し、deviceに格納 */
            device = atoi(input);

            if(device >= 1 && device < USERNUM){
                printf("イベント(0:offhook   1:onhook   2:dial   3:group)>");
                scanf("%d", &event);

                if(event == 0 || event == 1){
                    tk_select(device, event, telnum);

                }else if(event == 2){
                    printf("電話番号またはパスワード >");
                    scanf("%d", &telnum);
                    tk_select(device, event, telnum);

                }else if(event == 3){
                    tk_select(device, event, telnum);

                }else{
                    printf("イベント無効です!\n");
                }

            }else{
                printf("端末番号が違います.\n");
            }
        }
    }

    return 0;
}