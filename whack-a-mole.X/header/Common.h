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

/* -------------------------------------------------- */
// パブリック関数
/* -------------------------------------------------- */

void ItoStr(uint16_t i_value, uint8_t *o_strAdd, uint8_t i_strLen);
char *utoa(unsigned int value, char *s, int radix);

/* -------------------------------------------------- */

// ---------------------------------------------
// グローバル変数
// =--------------------------------------------

extern uint8_t char_blank;
extern uint8_t str_blank[8];

/* -------------------------------------------------- */

#endif /* COMMON_H */
