#include "../header/Input.h"

void detectPushSW(void){
    InputPort = (uint8_t)(~PORTA & 0x2F);
    detectPushSWX(&sw1);
    detectPushSWX(&sw2);
    detectPushSWX(&sw3);
    detectPushSWX(&sw4);
    detectPushSWX(&sw5);
}

void detectPushSWX(SWType* i_swType){
    //SWXに対応する処理が終了しているか
    if(!(SWState & i_swType.valueForCompareSW)){
        //SWが押されているか
        if(InputPort & i_swType.valueForCompareSW){
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;
            //チャタリング処理回数は3以上か
            if(i_swType->chattCount>=3){
                i_swType->isPushed = 1;
                //SW入力値が1かつ、前回のSW入力値が0か
                if(i_swType->isPushed == 1 &&
                   i_swType->lastPushed == 0){
                    SWState |= valueForCompareSW;
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
        //SWが押されていないとき
        else{
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;            
        }
        i_swType->lastPushed = i_swType->isPushed;
    }
    //SWXに対応する処理が終了していないとき
    else{
        //何もしない
    }
}