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
    MOLE_STATE_POP,  //モグラ出現
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

/* モグラ全体処理関数
 * モグラ1-4の処理を行う
 */
void MoleManager(void);

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

#ifdef NOUSE
/* モグラ出現関数
 * モグラの出現処理を行う
 * 入力 MoleType * i_mole モグラ構造体
 */
void OutOfHole(MoleType *);

/* モグラ撃退関数
 * モグラの撃退処理を行う
 * 入力 MoleType * i_mole モグラ構造体
 */
void Attacked(MoleType *);

/* モグラ未出現関数
 * モグラの未出現処理を行う
 * 入力 MoleType * i_mole モグラ構造体
 */
void BackToHole(MoleType *);

/* モグラ全体タイマ処理関数
 * モグラのタイマ処理を行う
 */
void MoleTimerProcess(void);

/* モグラ出現判定関数
 * モグラの出現を判定する
 * 入力 uint16_t 1_decisionNumber 出現判定値
 * 出力 bool TRUE モグラ出現
 *           FALSE　モグラ未出現
 */
bool PopDecision(uint16_t);

/* モグラ出現時間取得関数
 * モグラの出現時間を取得する
 * 入力 uint8_t i_level 難易度
 *      uint8_t i_time 残り時間
 * 出力 uint8_t popTime 出現時間
 */
uint8_t GetPopTime(uint8_t, uint8_t);

#endif

#ifdef __cplusplus
}
#endif

#endif /* MOLE_H */
