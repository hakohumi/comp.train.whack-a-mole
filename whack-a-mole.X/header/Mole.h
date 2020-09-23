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

//モグラ状態の定義
typedef enum MoleStateType_Type {
    MOLE_STATE_HOLE,  //モグラ未出現
    MOLE_STATE_POP,  //モグラ出現
    MOLE_STATE_HIT    //モグラ撃退
} MoleStateType;

/* モグラ構造体
 * uint8_t moleNum モグラの番号
 * bool popFlag モグラ出現フラグ 
 * uint8_t state モグラの状態
 * uint8_t popTime モグラ出現時間
 */
typedef struct {
    uint8_t moleNum;
    bool popFlag;
    uint8_t state;
    uint8_t popTime;
    uint8_t valueForCompareSW;
} MoleType;

//モグラ1-4
extern MoleType mole1;
extern MoleType mole2;
extern MoleType mole3;
extern MoleType mole4;

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
