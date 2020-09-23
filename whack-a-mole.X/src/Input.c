#include "Input.h"

#include "xc.h"

SWType sw1 = { 0, 0, SW1, 0};
SWType sw2 = { 0, 0, SW2, 0};
SWType sw3 = { 0, 0, SW3, 0};
SWType sw4 = { 0, 0, SW4, 0};
SWType sw5 = { 0, 0, SW5, 0};

//ポート値
uint8_t InputPort;

//SW入力状態
uint8_t SWState;

uint8_t getCompareSW(uint8_t i_Num){
    uint8_t l_compareSW;

    switch (i_Num) {
        case 1:
            l_compareSW = SW1;
            break;
        case 2:
            l_compareSW = SW2;
            break;
        case 3:
            l_compareSW = SW3;
            break;
        case 4:
            l_compareSW = SW4;
            break;
        case 5:
            l_compareSW = SW5;
        default:
            break;
    }
    return l_compareSW;
}

void DetectPushSW(void) {
    //ポート値(1~3,5,7ビット目が各SWに対応、SWが押されているとき1)
    InputPort = (uint8_t)(~PORTA & 0x057);
    //SW1~5のSW押下を検知
    detectPushSWX(&sw1);
    detectPushSWX(&sw2);
    detectPushSWX(&sw3);
    detectPushSWX(&sw4);
    detectPushSWX(&sw5);
}

void detectPushSWX(SWType *i_swType) {
    //SWXに対応するメイン処理が終了しているか
    if (!(SWState & i_swType->valueForCompareSW)) {
        //SWXが押されているか
        if (InputPort & i_swType->valueForCompareSW) {
            //チャタリング処理回数は3以上か
            if (i_swType->chattCount >= 2) {
                //SW入力値を1にする
                i_swType->isPushed = 1;
                //SW入力値が1かつ、前回のSW入力値が0か？
                if (i_swType->isPushed == 1 &&
                    i_swType->lastPushed == 0) {
                    //SWStateを更新
                    SWState |= i_swType->valueForCompareSW;
                } else {
                    //何もしない
                }
            }
            //チャタリング処理回数が3未満のとき
            else {
                i_swType->chattCount++;
            }
        }
        //SWXが押されていないとき
        else {
            i_swType->chattCount = 0;
            i_swType->isPushed   = 0;
        }
        i_swType->lastPushed = i_swType->isPushed;
    }
    //SWXに対応するメイン処理が終了していないとき
    else {
        //何もしない
    }
}