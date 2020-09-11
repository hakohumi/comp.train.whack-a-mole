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
// Co = 0, RS = 0, Control byte = 0;
#define CONTROLE_BYTE (uint8_t)(0x00)
// RSビットが立っているとき
#define WR_CONTROLE_BYTE (uint8_t)(0x40)
// 1つコマンド 8文字表示
#define MAX_BUF_SIZE 9

// LCDの1行目、2行目の意味の引数
#define LINE_FIRST 0x00
#define LINE_SECOND 0x01

#define LINE_DIGITS_MAX 8
#define LCD_SET_POS_DB7 0x80

// 10進数の最大の数
#define DECIMAL_MAX 9
// ClearDisplay コマンドのデータ部
#define CMD_LCD_CLR_DISPLAY 0x01

// Display ON コマンドのデータ部
#define CMD_LCD_DISPLAY_ON 0x0C

// Display OFF コマンドのデータ部
#define CMD_LCD_DISPLAY_OFF 0x08

// UpdateLCDフラグをONにする
#define SetUpdateLCDFlg()  \
    do {                   \
        UpdateLCDFlg = ON; \
    } while (0)
#define ClrUpdateLCDFlg()   \
    do {                    \
        UpdateLCDFlg = OFF; \
    } while (0)

void InitLCD(void);

// LCD上の書き込む位置を指定する
inline void SetPosLCD(uint8_t i_pos);   // アドレス指定
inline void SetPosLineLCD(bool i_row);  // 1行目か2行目の先頭を指定

void Write1LineToLCD(uint8_t *i_str, uint8_t i_len);

void ClrLineDisplay(uint8_t i_line);
void ClrDisplay(void);

uint8_t *ItoStr(uint8_t i_value, uint8_t *o_strAdd, uint8_t i_strLen);

// LCDResetFlg
// LCDのリセット処理を、このリセット処理が終わってから行うようにするためのフラグ
inline void SetLCDResetFlg(void);  // ON
// inline void ClrLCDResetFlg(void);  // OFF

void DisplayON(void);
void DisplayOFF(void);

extern bool UpdateLCDFlg;
// LCDのリセット処理を、このリセット処理が終わってから行うようにするためのフラグ
extern bool LCDResetFlg;

char *utoa(unsigned int value, char *s, int radix);

#endif /* LCDCLASS_H */
