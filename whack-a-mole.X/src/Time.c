#include "../header/Time.h"

void Penalty(void){
    if(Time <= 2){
        Time = 0;
    }
    else if(Time <= 60){
        Time -= 3;
    }
    else{
        //�������Ȃ�
    } 
}

void CountDown(void){
    if(Time){
        Time--;
    }
    else{
        //�������Ȃ�
    }
}