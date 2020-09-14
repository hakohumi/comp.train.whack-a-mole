#include "../header/Time.h"

void Penalty(void){
    //残り時間2以下の処理
    if(Time <= 2){
        //残り時間を0にする
        Time = 0;
    }
    //残り時間60以下の処理
    else if(Time <= 60){
        //残り時間を3減少する
        Time -= 3;
    }
    else{
        //何もしない
    } 
}

void CountDown(void){
    //残り時間が0でないとき
    if(Time){
        //残り時間を1減少させる
        Time--;
    }
    else{
        //何もしない
    }
}