#include "Input.h"
#include "xc.h"

void DetectPushSW(void){
    //ポート値(1~3,5,7ビット目が各SWに対応、SWが押されているとき1)
    InputPort = (uint8_t)(~PORTA & 0x057);
    //SW1~5のSW押下を検知
    detectPushSWX(&sw1);
    detectPushSWX(&sw2);
    detectPushSWX(&sw3);
    detectPushSWX(&sw4);
    detectPushSWX(&sw5);
}

void detectPushSWX(SWType* i_swType){
    //SWXに対応するメイン処理が終了しているか
    if(!(SWState & i_swType->valueForCompareSW)){
        //SWXが押されているか
        if(InputPort & i_swType->valueForCompareSW){
            //チャタリング処理回数は3以上か
            if(i_swType->chattCount>=2){
                //SW入力値を1にする
                i_swType->isPushed = 1;
                //SW入力値が1かつ、前回のSW入力値が0か？
                if(i_swType->isPushed == 1 &&
                   i_swType->lastPushed == 0){
                    //SWStateを更新
                    SWState |= i_swType->valueForCompareSW;
                    RB3 = ~RB3;
                }
                else{
                    //何もしない
                }
            }
            //チャタリング処理回数が3未満のとき
            else{
                i_swType->chattCount++;
            }
        }
        //SWXが押されていないとき
        else{
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;            
        }
        i_swType->lastPushed = i_swType->isPushed;
    }
    //SWXに対応するメイン処理が終了していないとき
    else{
        //何もしない
    }
}