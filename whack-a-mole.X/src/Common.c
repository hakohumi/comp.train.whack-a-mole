#include "Common.h"

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */

uint8_t itochar(uint8_t value);

#ifdef NOUSE
char *utoa(unsigned int value, char *s, int radix);
#endif
/* -------------------------------------------------- */

// ---------------------------------------------
// 文字リテラル
// =--------------------------------------------

uint8_t STR_CHAR_BLANK   = ' ';
uint8_t *STR_LINE_BLANK  = "        ";
uint8_t *STR_2LINE_BLANK = "                ";
uint8_t *STR_ERROR       = "error";

/* -------------------------------------------------- */

// 数値一文字をchar型へ変換

uint8_t itochar(uint8_t value) {
    if (value > DECIMAL_MAX) {
        return STR_CHAR_BLANK;
    }
    return "0123456789"[value];
}

// 受取った数値を文字列へ変換
void ItoStr(uint16_t i_value, uint8_t *o_strAdd, uint8_t i_strLen) {
    while (i_strLen != 0) {
        o_strAdd[i_strLen - 1] = itochar(i_value % 10);
        i_value /= 10;
        i_strLen--;
    }
}

#ifdef NOUSE

// 拾ってきた関数
// なぜか動かない
char *utoa(unsigned int value, char *s, int radix) {
    char *s1 = s;
    char *s2 = s;

    do {
        *s2++ = "0123456789abcdefghijklmnopqrstuvwxyz"[value % radix];
        value /= radix;
    } while (value > 0);

    *s2-- = '\0';

    while (s1 < s2) {
        char c = *s1;
        *s1++  = *s2;
        *s2--  = c;
    }
    return s;
}

#endif