#include "Input.h"
#include "xc.h"

void DetectPushSW(void){
    InputPort = (uint8_t)(~PORTA & 0x03F);
    detectPushSWX(&sw1);
    detectPushSWX(&sw2);
    detectPushSWX(&sw3);
    detectPushSWX(&sw4);
    detectPushSWX(&sw5);
}

void detectPushSWX(SWType* i_swType){
    //SWXに対応する�?��?が終�?して�?るか
    if(!(SWState & i_swType->valueForCompareSW)){
        //SWが押されて�?るか
        if(InputPort & i_swType->valueForCompareSW){
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;
            //チャタリング処�?回数は3以上か
            if(i_swType->chattCount>=3){
                i_swType->isPushed = 1;
                //SW入力�?��?1かつ、前回�?�SW入力�?��?0�?
                if(i_swType->isPushed == 1 &&
                   i_swType->lastPushed == 0){
                    SWState |= i_swType->valueForCompareSW;
                }
                else{
                    //何もしな�?
                }
            }
            //チャタリング処�?回数�?3未�?のと�?
            else{
                i_swType->chattCount++;
            }
        }
        //SWが押されて�?な�?と�?
        else{
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;            
        }
        i_swType->lastPushed = i_swType->isPushed;
    }
    //SWXに対応する�?��?が終�?して�?な�?と�?
    else{
        //何もしな�?
    }
}