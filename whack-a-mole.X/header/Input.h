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
SWType sw1 = { 0, 0, SW1, 0};
SWType sw2 = { 0, 0, SW2, 0};
SWType sw3 = { 0, 0, SW3, 0};
SWType sw4 = { 0, 0, SW4, 0};
SWType sw5 = { 0, 0, SW5, 0};

//ポート値
uint8_t InputPort;

//SW入力状態
uint8_t SWState;

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

