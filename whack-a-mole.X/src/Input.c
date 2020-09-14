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
    
}