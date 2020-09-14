#include "Mole.h"
#include "Input.h"
#include "../header/Timer.h"
#include "Score.h"

void MoleManager(void){
    MoleXProcess(&mole1);
    MoleXProcess(&mole2);
    MoleXProcess(&mole3);
    MoleXProcess(&mole4);
}

void MoleXProcess(MoleType* i_moleX){
    switch(i_moleX->state){
        //モグラ未出現時の処理
        case HOLE:
            //モグラ出現処理
            if(i_moleX->popFlag){
                OutOfHole(&i_moleX);
                i_moleX->popFlag = 0; //(OFF)
            }
            //ペナルティ処理
            else{
                if(SWState && i_moleX->valueForCompareSW){
                    Penalty(void);
                }
                else{
                    //何もしない
                }
            }
            break;
        //モグラ出現時の処理
        case MOLE:
            //モグラ撃退処理
            if(i_moleX->popTime){
                if(SWState && i_moleX->valueForCompareSW){
                    Attacked(&i_moleX);
                }
                else{
                    //何もしない
                }
            }
            //モグラ未出現(穴に戻る)処理
            else{
                BackToHole(&i_moleX);
            }
            break;
        //モグラ撃退時処理
        case HIT:
            //モグラ未出現(穴に戻る)処理
            if(!i_moleX->popTime){
                BackToHole(&i_moleX);
            }
            else{
                //何もしない
            }
            break;
        default:
            break;  
    }
}

//モグラ出現処理
void OutOfHole(MoleType* i_moleX){
    i_moleX->state = (uint8_t)MOLE;
    //SetpopTime() 出現時間設定
    //WriteToBuffer
}

//モグラ撃退処理
void Attacked(MoleType* i_moleX){
    i_moleX->state = (uint8_t)HIT;
    i_moleX->popTime = 30;
    IncScore();
    //WriteToBuffer
}

//モグラ未出現(穴に戻る)処理
void BackToHole(MoleType* i_moleX){
    i_moleX->state = (uint8_t)HOLE;
    //WriteToBuffer
}
