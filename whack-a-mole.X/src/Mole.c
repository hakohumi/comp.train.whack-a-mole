#include "Mole.h"
#include "Input.h"
#include "Timer.h"
#include "Score.h"
#include "Rand.h"

void MoleManager(void){
    MoleXProcess(&mole1);
    MoleXProcess(&mole2);
    MoleXProcess(&mole3);
    MoleXProcess(&mole4);
}

void MoleXProcess(MoleType* i_moleX){
    switch(i_moleX->state){
        //モグラ穴の処理
        case HOLE:
            //モグラ出現フラグONか
            if(i_moleX->popFlag){
                OutOfHole(&i_moleX);
                i_moleX->popFlag = 0; //(OFF)
            }
            else{
                //お手付き処理
                if(SWState && i_moleX->valueForCompareSW){
                    Penalty();
                }
            }
            break;
        //モグラ出現処理
        case MOLE:
            if(i_moleX->popTime){
                //モグラ撃退
                if(SWState && i_moleX->valueForCompareSW){
                    Attacked(&i_moleX);
                }
            }
            //モグラ穴に戻る処理
            else{
                BackToHole(&i_moleX);
            }
            break;
        //モグラ撃退処理
        case HIT:
            //モグラの穴に戻る処理
            if(!i_moleX->popTime){
                BackToHole(&i_moleX);
            }
            break;
        default:
            break;  
    }
}

//モグラ出現処理
void OutOfHole(MoleType* i_moleX){
    i_moleX->state = (uint8_t)MOLE;
    //SetpopTime() モグラ出現時間決定
    //WriteToBuffer
}

//モグラ撃退処理
void Attacked(MoleType* i_moleX){
    i_moleX->state = (uint8_t)HIT;
    i_moleX->popTime = 30;
    IncScore();
    //WriteToBuffer
}

//モグラの穴に戻る処理
void BackToHole(MoleType* i_moleX){
    i_moleX->state = (uint8_t)HOLE;
    //WriteToBuffer
}

bool PopDecision(uint16_t i_decisionNumber){
    bool retVal;
    if(GetRand()<i_decisionNumber){
        retVal = true;
    }
    else{
        retVal = false;
    }
    return retVal;
}

uint8_t GetpopTime(uint8_t i_level, uint8_t i_time){
    uint8_t popTime;
    uint8_t minPopTime;
    uint8_t maxPopTime;
    uint8_t randPer100 = (uint8_t)(GetRand()%100);
    switch(i_level){
        case EASY:
            minPopTime = 100;   //1000ms
            maxPopTime = 200;
            break;
        case NORMAL:
            minPopTime = 50;
            maxPopTime = 150;
            break;
        case HARD:
            minPopTime = 20;
            maxPopTime = 100;
            break;
        default:
            break;
    }
    
            
}
