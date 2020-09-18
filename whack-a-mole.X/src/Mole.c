#include "Mole.h"

#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Rand.h"
#include "Score.h"
#include "State.h"
#include "Timer.h"

uint8_t MinMolePopTime;
uint8_t MaxMolePopTime;

void MoleManager(void) {
    MoleXProcess(&mole1);
    MoleXProcess(&mole2);
    MoleXProcess(&mole3);
    MoleXProcess(&mole4);
}

void MoleXProcess(MoleType *i_moleX) {
    switch (i_moleX->state) {
            //モグラ穴の処理
        case MOLE_STATE_HOLE:
            //モグラ出現フラグONか
            if (i_moleX->popFlag) {
                //OutOfHole(&i_moleX);
                i_moleX->state   = (uint8_t)MOLE_STATE_POP;
                i_moleX->popTime = MinMolePopTime + ((MaxMolePopTime - MinMolePopTime) / 60) * RemaingTime;
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
            if (i_moleX->popTime) {
                //モグラ撃退
                if (SWState & i_moleX->valueForCompareSW) {
                    //Attacked(&i_moleX);
                    i_moleX->state   = (uint8_t)MOLE_STATE_HIT;
                    i_moleX->popTime = 30;
                    IncScore();
                    WriteToBufferInt(1, Score, 3);
                    WriteToBufferMole(i_moleX->moleNum, MOLE_STATE_HIT);
                    SWState &= ~i_moleX->valueForCompareSW;
                }
            }  //モグラ穴に戻る処理
            else {
                //BackToHole(&i_moleX);
                i_moleX->state = (uint8_t)MOLE_STATE_HOLE;
                WriteToBufferMole(i_moleX->moleNum, MOLE_STATE_HOLE);
            }
            break;
            //モグラ撃退処理
        case MOLE_STATE_HIT:
            //モグラの穴に戻る処理
            if (!i_moleX->popTime) {
                //BackToHole(&i_moleX);
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
        decisionNumber = (molePopProbability + (molePopProbability / 60) * (60 - RemaingTime)) * (Level+1);
        randVal        = GetRand();
        //乱数がモグラ出現判定値より小さいとき、popFlagを立てる
        //        if(PopDecision(decisionNumber)){
        if (randVal < decisionNumber) {
            i_mole->popFlag = 1;
        }
    //モグラの状態が未出現以外のとき、出現時間を減少
    } else {
        if (i_mole->popTime) {
            i_mole->popTime--;
        }
    }
}

#ifdef NOUSE

//モグラ出現処理

void OutOfHole(MoleType *i_moleX) {
    i_moleX->state   = (uint8_t)MOLE_STATE_POP;
    i_moleX->popTime = GetPopTime(Level, RemaingTime);  //モグラ出現時間決定
}

//モグラ撃退処理

void Attacked(MoleType *i_moleX) {
    i_moleX->state   = (uint8_t)MOLE_STATE_HIT;
    i_moleX->popTime = 30;
    IncScore();
}

//モグラの穴に戻る処理

void BackToHole(MoleType *i_moleX) {
    i_moleX->state = (uint8_t)MOLE_STATE_HOLE;
}

void MoleTimerProcess(void) {
    if (SystemState.displayState == PLAYING_GAME) {
        MoleXTimerProcess(&mole1);
        MoleXTimerProcess(&mole2);
        MoleXTimerProcess(&mole3);
        MoleXTimerProcess(&mole4);
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
    }  //randPer100が10%-40%以内(30%)
    else if (randVal < PERCENT40_16BIT) {
        //0x7F以下のとき、左シフト
        if (popTime < 0x80) {
            popTime <<= 1;
        }  //0x80以上のとき、maxPopTime
        else {
            popTime = maxPopTime;
        }
    }  //それ以外(60%)
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

#endif