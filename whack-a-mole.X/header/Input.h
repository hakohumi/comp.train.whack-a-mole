/* 
 * File:   Input.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:13
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef INPUT_H
#define	INPUT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
//SWに対応するポートの位置
typedef enum SWPortPosType_Type{
    SW1 = 0x01, 
    SW2 = 0x02,
    SW3 = 0x04,
    SW4 = 0x10,
    SW5 = 0x40
} SWPortPosType;

//SW構造体
typedef struct {
    bool isPushed;
    bool lastPushed;
    uint8_t valueForCompareSW;
    uint8_t chattCount;
} SWType;

//SW1-5
extern SWType sw1;
extern SWType sw2;
extern SWType sw3;
extern SWType sw4;
extern SWType sw5;

//ポート値
extern uint8_t InputPort;

//SW入力状態
extern uint8_t SWState;

/* 入力ポート値ビット位置取得関数
 * 引数に応じたRAのビット位置を返す
 * 入力 uint8_t i_Num 番号(1-5) 
 * 出力 uint8_t RAビット位置
 */
uint8_t getCompareSW(uint8_t);

/* SW検知関数
 * SWを検知する
 */
void DetectPushSW(void);

/* SWX検知関数
 * SW1つの検知を行う
 * 入力 SWType * i_sw SW構造体
 */
void detectPushSWX(SWType*); 

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */

