#include "Mole.h"

#include "Buzzer/Buzzer.h"
#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Rand.h"
#include "Score.h"
#include "State.h"
#include "Timer.h"

//モグラ基準出現確率(難易度EASYで30匹程度)
#define MOLE_POP_BASE_PROBABIRITY 81

MoleType mole1 = {1, 0, 0, 0, SW1};
MoleType mole2 = {2, 0, 0, 0, SW2};
MoleType mole3 = {3, 0, 0, 0, SW3};
MoleType mole4 = {4, 0, 0, 0, SW4};

uint8_t MinMolePopTime;
uint8_t MaxMolePopTime;

void MoleXProcess(MoleType *i_moleX) {
    switch (i_moleX->state) {
            //モグラ穴の処理
        case MOLE_STATE_HOLE:
            //モグラ出現フラグONか
            if (i_moleX->popFlag) {
                i_moleX->state   = (uint8_t)MOLE_STATE_POP;
                if(RemaingTime<=60){
                    i_moleX->popTime = MinMolePopTime + ((MaxMolePopTime - MinMolePopTime) / 60) * RemaingTime;   
                } else {
                    i_moleX->popTime = 0;
                }
                WriteToBufferMole(i_moleX->moleNum, MOLE_STATE_POP);
                i_moleX->popFlag = 0;  //(OFF)
            } else {
                //お手付き処理
                if (SWState & i_moleX->valueForCompareSW) {
                    Penalty();
                    SWState &= ~i_moleX->valueForCompareSW;
                    WriteToBufferInt(6, RemaingTime, 2);
                }
            }
            break;
            //モグラ出現処理
        case MOLE_STATE_POP:
            if (i_moleX->popTime > 0) {
                //モグラ撃退
                if (SWState & i_moleX->valueForCompareSW) {
                    //Attacked(&i_moleX);
                    i_moleX->state   = (uint8_t)MOLE_STATE_HIT;
                    i_moleX->popTime = 30;
                    IncScore();
                    WriteToBufferInt(1, Score, 3);
                    WriteToBufferMole(i_moleX->moleNum, MOLE_STATE_HIT);
                    SWState &= ~i_moleX->valueForCompareSW;
                    PlaySE();
                }
                //モグラ穴に戻る処理
            } else {
                i_moleX->state = (uint8_t)MOLE_STATE_HOLE;
                WriteToBufferMole(i_moleX->moleNum, MOLE_STATE_HOLE);
            }
            break;
            //モグラ撃退処理
        case MOLE_STATE_HIT:
            //モグラの穴に戻る処理
            if (!i_moleX->popTime) {
                i_moleX->state = (uint8_t)MOLE_STATE_HOLE;
                WriteToBufferMole(i_moleX->moleNum, MOLE_STATE_HOLE);
            }
            break;
        default:
            break;
    }
}

void MoleXTimerProcess(MoleType *i_mole) {
    uint16_t molePopProbability = 81;
    uint16_t decisionNumber;
    uint16_t randVal;

    if (i_mole->state == MOLE_STATE_HOLE) {
        //モグラ出現判定値を取得
        decisionNumber = (molePopProbability + (molePopProbability / 60) * (60 - RemaingTime)) * (Level + 1);
        randVal        = GetRand();
        //乱数がモグラ出現判定値より小さいとき、popFlagを立てる
        if (randVal < decisionNumber) {
            i_mole->popFlag = 1;
        }
        //モグラの状態が未出現以外のとき、出現時間を減少
    } else {
        if (i_mole->popTime > 0) {
            i_mole->popTime--;
        }
    }
}
