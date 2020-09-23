/* 
 * File:   Mole.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:34
 */

#include <stdbool.h>
#include <stdint.h>

#include "Input.h"

#ifndef MOLE_H
#define MOLE_H

#ifdef __cplusplus
extern "C" {
#endif

//SW
typedef enum MoleStateType_Type {
    MOLE_STATE_HOLE,  //モグラ未出現
    MOLE_STATE_POP,   //モグラ出現
    MOLE_STATE_HIT    //モグラ撃退
} MoleStateType;

/* モグラ構造体
 * uint8_t state モグラの状態
 * uint8_t popTime モグラ出現時間
 * bool popFlag モグラ出現フラグ
 */
typedef struct {
    uint8_t state;
    uint8_t popTime;
    uint8_t valueForCompareSW;
    uint8_t moleNum;
    bool popFlag;
} MoleType;

//モグラ1-4
MoleType mole1 = {0, 0, SW1, 1, 0};
MoleType mole2 = {0, 0, SW2, 2, 0};
MoleType mole3 = {0, 0, SW3, 3, 0};
MoleType mole4 = {0, 0, SW4, 4, 0};

//最大モグラ出現時間(難易度によって変わる)
extern uint8_t MinMolePopTime;
//最小モグラ出現時間
extern uint8_t MaxMolePopTime;

/* モグラX処理関数
 * モグラ1匹に対する処理を行う
 * 入力 MoleType * i_mole モグラ構造体
 */
void MoleXProcess(MoleType *);

/* モグラXタイマ処理
 * モグラ1匹に対するタイマ処理を行う
 * 入力 MoleType * i_mole モグラ構造体
 */
void MoleXTimerProcess(MoleType *);

#ifdef __cplusplus
}
#endif

#endif /* MOLE_H */
