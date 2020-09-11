#include "../header/Time.h"

void Penalty(void){
    if(Time <= 2){
        Time = 0;
    }
    else if(Time <= 60){
        Time -= 3;
    }
    else{
        //‰½‚à‚µ‚È‚¢
    } 
}

void CountDown(void){
    if(Time){
        Time--;
    }
    else{
        //‰½‚à‚µ‚È‚¢
    }
}