/* 
 * File:   Mole.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:34
 */

#include <stdint.h>

#ifndef MOLE_H
#define	MOLE_H

#ifdef	__cplusplus
extern "C" {
#endif

//モグラの状態を定義
typedef enum MoleStateType_Type{
    HOLE,   //モグラの穴
    MOLE,   //モグラ出現中
    HIT     //モグラ撃退
} MoleStateType;

/* モグラ構造体
 * state モグラの状態 
 * popTime モグラの出現時間
 * popFlag モグラの出現判定 ONで出現
 */
typedef struct {
    uint8_t state;
    uint8_t popTime;
    uint8_t valueForCompareSW;
    bool popFlag;
} MoleType;

//モグラ1-4
MoleType mole1 = {0,0,0x00,0};     
MoleType mole2 = {0,0,0x01,0};
MoleType mole3 = {0,0,0x02,0};
MoleType mole4 = {0,0,0x04,0};

/* モグラ処理関数
 * モグラ1-4の処理を行う関数
 */
void MoleManager(void);

/* モグラX処理関数
 * モグラ1匹に対する処理を行う関数
 * 入力 モグラの番号(1-4)
 */ 
void MoleXProess(MoleType*);

/* モグラ出現関数
 * 入力 モグラの番号(1-4)
 * 出力 入力に対応するモグラのstateをMOLEに
 * 　　 popTimeをランダムに決定する
 */
void OutOfHole(MoleType*);

/* モグラ撃退関数
 * 入力 モグラの番号(1-4)
 * 出力 入力に対応するモグラのstateをHITに
 * 　　 popTimeを固定値で決定する
 */
void Attacked(MoleType*);

/* モグラ未出現関数
 * 入力 モグラの番号(1-4)
 * 出力 入力に対応するモグラのstateをHOLEにする
 */
void BackToHole(MoleType*);

/* モグラ出現判定関数
 * 入力 モグラ出現判定値(0x00-0xFFFF)
 *      出現判定値は別途テーブルから取得する
 * 　　 出現判定値が0x7FFFの場合、50%の確率でTRUEを返す
 * 出力 TRUE    モグラを出現させる
 * 　　 False   モグラを出現させない
 */
bool PopDecision(uint16_t);

#ifdef	__cplusplus
}
#endif

#endif	/* MOLE_H */

