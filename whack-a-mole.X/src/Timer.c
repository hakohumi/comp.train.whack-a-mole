#include "../header/Timer.h"

//残り時間
uint8_t RemaingTime = 0;

//乱数規定値取得用時間
uint16_t TimeForRand;

void Penalty(void) {
    //残り時間2以下のとき
    if (RemaingTime <= 2) {
        //残り時間を0にする
        RemaingTime = 0;
    }
    //残り時間60以下のとき
    else if (RemaingTime <= 60) {
        //残り時間を3減少する
        RemaingTime -= 3;
    } else {
        //何もしない
    }
}

void CountDown(void) {
    //残り時間が0でないとき
    if (RemaingTime > 0) {
        //残り時間
        RemaingTime--;
    } else {
        //何もしない
    }
}