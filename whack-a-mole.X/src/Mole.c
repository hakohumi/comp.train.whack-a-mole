#include "Mole.h"

#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Rand.h"
#include "Score.h"
#include "State.h"
#include "Timer.h"

#define POP_PROBABILITY_PER_16BIT 323
#define PERCENT10_16BIT 0x1999
#define PERCENT40_16BIT 0x6664

#define MIN_POP_DECISION_TIME 10

uint8_t chr_Hole = '_';
uint8_t chr_Mole = 'M';
uint8_t chr_Hit  = 'A';

void writeMole(uint8_t, uint8_t);

void writeMole(uint8_t i_compareSW, uint8_t i_chr) {
    uint8_t str_MolePos;

    switch (i_compareSW) {
        case SW1:
            str_MolePos = 9;
            break;
        case SW2:
            str_MolePos = 11;
            break;
        case SW3:
            str_MolePos = 13;
            break;
        case SW4:
            str_MolePos = 15;
            break;
        default:
            break;
    }
    str_PlayingGameState[str_MolePos] = i_chr;
    WriteToBuffer(str_PlayingGameState, 16);
}

void MoleManager(void) {
    MoleXProcess(&mole1);
    MoleXProcess(&mole2);
    MoleXProcess(&mole3);
    MoleXProcess(&mole4);
}

void MoleXProcess(MoleType *i_moleX) {
    uint8_t minPopTime = 100;
    uint8_t maxPopTime = 200;

    switch (i_moleX->state) {
        //モグラ穴の処理
        case HOLE:
            //モグラ出現フラグONか
            if (i_moleX->popFlag) {
                //OutOfHole(&i_moleX);
                i_moleX->state   = (uint8_t)MOLE;
                i_moleX->popTime = minPopTime + ((maxPopTime - minPopTime) / 60) * Time;
                WriteToBufferMole(i_moleX->moleNum, MOLE);
                i_moleX->popFlag = 0;  //(OFF)
            } else {
                //お手付き処理
                if (SWState && i_moleX->valueForCompareSW) {
                    Penalty();
                }
            }
            break;
        //モグラ出現処理
        case MOLE:
            if (i_moleX->popTime) {
                //モグラ撃退
                if (SWState && i_moleX->valueForCompareSW) {
                    //Attacked(&i_moleX);
                    i_moleX->state   = (uint8_t)HIT;
                    i_moleX->popTime = 30;
                    IncScore();

                    WriteToBufferMole(i_moleX->moleNum, HIT);
                }
            }
            //モグラ穴に戻る処理
            else {
                //BackToHole(&i_moleX);
                i_moleX->state = (uint8_t)HOLE;
            }
            break;
        //モグラ撃退処理
        case HIT:
            //モグラの穴に戻る処理
            if (!i_moleX->popTime) {
                //BackToHole(&i_moleX);
                i_moleX->state = (uint8_t)HOLE;
                WriteToBufferMole(i_moleX->moleNum, HOLE);
            }
            break;
        default:
            break;
    }
}

//モグラ出現処理
void OutOfHole(MoleType *i_moleX) {
    i_moleX->state   = (uint8_t)MOLE;
    i_moleX->popTime = GetPopTime(Level, Time);  //モグラ出現時間決定
}

//モグラ撃退処理
void Attacked(MoleType *i_moleX) {
    i_moleX->state   = (uint8_t)HIT;
    i_moleX->popTime = 30;
    IncScore();
}

//モグラの穴に戻る処理
void BackToHole(MoleType *i_moleX) {
    i_moleX->state = (uint8_t)HOLE;
}

void MoleTimerProcess(void) {
    if (SystemState.displayState == PLAYING_GAME) {
        MoleXTimerProcess(&mole1);
        MoleXTimerProcess(&mole2);
        MoleXTimerProcess(&mole3);
        MoleXTimerProcess(&mole4);
    }
}

void MoleXTimerProcess(MoleType *i_mole) {
    uint16_t decisionNumber;
    uint16_t randVal;

    if (i_mole->state == HOLE) {
        decisionNumber = (POP_PROBABILITY_PER_16BIT / 60) * (60 - Time) * (Level + 1);
        randVal        = GetRand();
        //        if(PopDecision(decisionNumber)){
        if (randVal < decisionNumber) {
            i_mole->popFlag = 1;
        }
    } else {
        if (i_mole->popTime) {
            i_mole->popTime--;
        }
    }
}

bool PopDecision(uint16_t i_decisionNumber) {
    bool retVal;
    if (GetRand() < i_decisionNumber) {
        retVal = true;
    } else {
        retVal = false;
    }
    return retVal;
}

uint8_t GetPopTime(uint8_t i_level, uint8_t i_time) {
    uint8_t popTime;
    uint8_t minPopTime;
    uint8_t maxPopTime;
    uint8_t remaingTime = i_time;
    uint16_t randVal    = GetRand();

    //出現時間の最大値と最小値を決定
    switch (i_level) {
        case EASY:
            minPopTime = 100;  //1000ms
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
    if (remaingTime < MIN_POP_DECISION_TIME) {
        remaingTime = MIN_POP_DECISION_TIME;
    }

    //出現時間を計算
    popTime = minPopTime + ((maxPopTime - minPopTime) / 60) * i_time;

    //一定確率で出現時間を増減させる
    //randValが10%以内
    if (randVal < PERCENT10_16BIT) {
        //1ビット右シフト
        popTime >>= 1;
    }
    //randPer100が10%-40%以内(30%)
    else if (randVal < PERCENT40_16BIT) {
        //0x7F以下のとき、左シフト
        if (popTime < 0x80) {
            popTime <<= 1;
        }
        //0x80以上のとき、maxPopTime
        else {
            popTime = maxPopTime;
        }
    }
    //それ以外(60%)
    else {
        //popTimeを変更しない
    }

    //表示時間が最大値最小値を超えないようにする
    if (popTime < minPopTime) {
        popTime = minPopTime;
    }
    if (popTime > maxPopTime) {
        popTime = maxPopTime;
    }
    return popTime;
}
