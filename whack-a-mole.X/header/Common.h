/*
 * File:   Common.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:27 PM
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdint.h>

#define ON true
#define OFF false

// 楽譜の音階
// いずれ、MusicSheetが一つになった時に、MusicSheetのヘッダに入れる
// typedef enum {
//     REST,
//     DO_,
//     DO_SHARP,
//     RE,
//     RE_SHARP,
//     MI,
//     FA,
//     FA_SHARP,
//     SO,
//     SO_SHARP,
//     RA_,
//     RA_SHARP,
//     SI,
//     DO2,
//     RE2,
//     MI2,
//     FA2,
//     SO2,
//     RA2_,
//     SI2,
//     SCALE_NUM

// } ScaleType;

// REST
#define REST (0x00)
// DO
#define DO_ (0xEE)
// DO_SHARP
#define DO_SHARP (0xE1)
// RE
#define RE (0xD4)
// RE_SHARP
#define RE_SHARP (0xC8)
// MI
#define MI (0xBD)
// FA
#define FA (0xB2)
// FA_SHARP
#define FA_SHARP (0xA8)
// SO
#define SO (0x9F)
// SO_SHARP
#define SO_SHARP (0x96)
// RA
#define RA_ (0x8E)
// RA_SHARP
#define RA_SHARP (0x86)
// SI
#define SI (0x7E)
// DO2
#define DO2 (0x77)
// RE2
#define RE2 (0x6A)
// MI2
#define MI2 (0x5E)
// FA2
#define FA2 (0x59)
// SO2
#define SO2 (0x4F)
// RA2
#define RA2_ (0x47)
// SI2
#define SI2 (0x3F)
#define SCALE_NUM 19

// 10進数の最大の数
#define DECIMAL_MAX 9

// 文字列"エラー"の長さ
#define STR_ERROR_LEN 5

#define LCD_LINE_LEN 8

/* -------------------------------------------------- */
// パブリック関数
/* -------------------------------------------------- */

uint8_t itochar(uint8_t value);

/* -------------------------------------------------- */

// ---------------------------------------------
// グローバル変数
// =--------------------------------------------

extern uint8_t STR_CHAR_BLANK;
extern uint8_t *STR_LINE_BLANK;
extern uint8_t *STR_ERROR;

/* -------------------------------------------------- */

#endif /* COMMON_H */
