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
extern uint8_t *STR_2LINE_BLANK;
extern uint8_t *STR_ERROR;

/* -------------------------------------------------- */


#endif /* COMMON_H */
