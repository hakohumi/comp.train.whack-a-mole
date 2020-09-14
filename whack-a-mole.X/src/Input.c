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
    //SWX�ɑΉ����鏈�����I�����Ă��邩
    if(!(SWState & i_swType.valueForCompareSW)){
        //SW��������Ă��邩
        if(InputPort & i_swType.valueForCompareSW){
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;
            //�`���^�����O�����񐔂�3�ȏォ
            if(i_swType->chattCount>=3){
                i_swType->isPushed = 1;
                //SW���͒l��1���A�O���SW���͒l��0��
                if(i_swType->isPushed == 1 &&
                   i_swType->lastPushed == 0){
                    SWState |= valueForCompareSW;
                }
                else{
                    //�������Ȃ�
                }
            }
            //�`���^�����O�����񐔂�3�����̂Ƃ�
            else{
                i_swType->chattCount++;
            }
        }
        //SW��������Ă��Ȃ��Ƃ�
        else{
            i_swType->chattCount = 0;
            i_swType->isPushed = 0;            
        }
        i_swType->lastPushed = i_swType->isPushed;
    }
    //SWX�ɑΉ����鏈�����I�����Ă��Ȃ��Ƃ�
    else{
        //�������Ȃ�
    }
}