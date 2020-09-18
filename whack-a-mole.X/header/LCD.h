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

// mainの最初に呼ぶ
void LCDInitialize(void);

// LCDバッファに書き込む
// 引数：uint8_t i_str
// 16文字までの文字列の先頭アドレスを設定する
// 9文字目から自動的に改行される

// ちゃんと文字数を指定しないと、範囲外のデータも表示するので注意
void WriteToBuffer(uint8_t i_WriteStartPos, uint8_t *i_str, uint8_t i_strLen);
void WriteToBuffer2(uint8_t *i_str, uint8_t i_strLen);
void WriteToBufferFirst(uint8_t *i_str, uint8_t i_strLen);
void WriteToBufferSecond(uint8_t *i_str, uint8_t i_strLen);

// モグラの表示を切り替える
void WriteToBufferMole(uint8_t i_molePos, uint8_t i_moleState);

#ifdef NOUSE
// ゲーム前カウントダウン用
// 真ん中に1桁の数字を表示
void WriteToBufferCountDown(uint8_t i_time);

// 残り時間をバッファに上書きする
void WriteToBufferTime(uint8_t i_time);
void WriteToBufferScore(uint16_t i_score);

#endif

// 指定した位置に指定した桁数の数値を書き込む
void WriteToBufferInt(uint8_t i_WriteStartPos, uint16_t i_score, uint8_t i_Len);

// LCDバッファをLCDに書き込む
void BufferToLCD(void);

void ClrLCDBuffer(void);
void ClrLCDBufferLine(bool i_line);

inline void SetPosLineLCD(bool i_row);  // 1行目か2行目の先頭を指定

#ifdef NOUSE

// LCD上の書き込む位置を指定する
inline void SetPosLCD(uint8_t i_pos);  // アドレス指定

void ClrLineDisplay(uint8_t i_line);

#endif

void ClrDisplay(void);
void DisplayON(void);
void DisplayOFF(void);

// 文字列"エラー"をBufferに格納
void ErrorToBuffer(uint8_t num);

#endif /* LCDCLASS_H */
