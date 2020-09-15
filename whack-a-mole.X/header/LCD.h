/*
 * File:   LCD.h
 * Author: fuminori.hakoishi
 *
 * Created on 2020/09/10
 */

#ifndef LCDCLASS_H
#define LCDCLASS_H

#include "../mcc_generated_files/examples/i2c1_master_example.h"
#include "Common.h"

// (B0111110);
#define LCD_ADDR (i2c1_address_t)(0x3E)

// LCDの1行目、2行目の意味の引数
#define LINE_FIRST 0x00
#define LINE_SECOND 0x01

// UpdateLCDフラグをONにする
#define SetUpdateLCDFlg()  \
    do {                   \
        UpdateLCDFlg = ON; \
    } while (0)
#define ClrUpdateLCDFlg()   \
    do {                    \
        UpdateLCDFlg = OFF; \
    } while (0)

// mainの最初に呼ぶ
void LCDInitialize(void);

// LCD上の書き込む位置を指定する
inline void SetPosLCD(uint8_t i_pos);   // アドレス指定
inline void SetPosLineLCD(bool i_row);  // 1行目か2行目の先頭を指定

// LCDバッファに書き込む
// 引数：uint8_t i_str
// 16文字までの文字列の先頭アドレスを設定する
// 9文字目から自動的に改行される

void WriteToBuffer(uint8_t *i_str, uint8_t i_strLen);

// LCDバッファをLCDに書き込む
void BufferToLCD(void);

// 1行書き込む
void Write1LineToLCD(uint8_t *i_str, uint8_t i_len);

void ClrLineDisplay(uint8_t i_line);
void ClrDisplay(void);

// LCDResetFlg
// LCDのリセット処理を、このリセット処理が終わってから行うようにするためのフラグ
inline void SetLCDResetFlg(void);  // ON
// inline void ClrLCDResetFlg(void);  // OFF

void DisplayON(void);
void DisplayOFF(void);

// 文字列"エラー"をBufferに格納
void ErrorToBuffer(uint8_t num);

extern bool UpdateLCDFlg;
// LCDのリセット処理を、このリセット処理が終わってから行うようにするためのフラグ
extern bool LCDResetFlg;

#endif /* LCDCLASS_H */
