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

void ItoStr(uint16_t i_value, uint8_t *o_strAdd, uint8_t i_strLen);
char *utoa(unsigned int value, char *s, int radix);

/* -------------------------------------------------- */

// ---------------------------------------------
// グローバル変数
// =--------------------------------------------

extern uint8_t STR_CHAR_BLANK;
extern uint8_t *STR_LINE_BLANK;
extern uint8_t *STR_2LINE_BLANK;
extern uint8_t *STR_ERROR;

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// エラー番号
/* -------------------------------------------------- */

typedef enum {
    ERR_W_T_B_OVERSTRLEN,
    ERR_W_T_B_F_OVERSTRLEN,
    ERR_W_T_B_S_OVERSTRLEN,
    ERR_1,
} MY_ERROR;

/* -------------------------------------------------- */

#endif /* COMMON_H */
