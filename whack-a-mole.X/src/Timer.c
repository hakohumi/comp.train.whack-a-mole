#include "../header/Timer.h"

//残り時間
uint8_t Time = 0;

//乱数規定値取得用時間
uint16_t TimeForRand;

void Penalty(void) {
    //残り時間2以下のとき
    if (Time <= 2) {
        //残り時間を0にする
        Time = 0;
    }
    //残り時間60以下のとき
    else if (Time <= 60) {
        //残り時間を3減少する
        Time -= 3;
    } else {
        //何もしない
    }
}

void CountDown(void) {
    //残り時間が0でないとき
    if (Time) {
        //残り時間
        Time--;
    } else {
        //何もしない
    }
}