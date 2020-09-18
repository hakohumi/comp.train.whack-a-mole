#include "../header/Timer.h"

//残り時間
uint8_t Time = 0;

//乱数規定�?�用時間
uint16_t TimeForRand;

void Penalty(void) {
    //残り時間2以下�?�処�?
    if (Time <= 2) {
        //残り時間�?0にする
        Time = 0;
    }
    //残り時間60以下�?�処�?
    else if (Time <= 60) {
        //残り時間�?3減少す�?
        Time -= 3;
    } else {
        //何もしない
    }
}

void CountDown(void) {
    //残り時間�?0でな�?と�?
    if (Time) {
        //残り時間�?1減少させる
        Time--;
    } else {
        //何もしない
    }
}