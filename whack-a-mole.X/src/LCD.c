
#include "LCD.h"

#include <mcc.h>

#include "Common.h"
#include "examples/i2c1_master_example.h"

/* -------------------------------------------------- */
// プライベートなdefine
/* -------------------------------------------------- */

// LCDの行頭のアドレス
#define LINE_FIRST_ADDR 0x00
#define LINE_SECOND_ADDR 0x40

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

static uint8_t LCDBuffer[16];

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// グローバル変数
/* -------------------------------------------------- */

bool UpdateLCDFlg = OFF;
// LCDのリセット処理を、このリセット処理が終わってから行うようにするためのフラグ
bool LCDResetFlg = OFF;

/* -------------------------------------------------- */

// LCDの初期化
// *** ST7032iに対して、書き込みフォーマット ***
// ①まず、7bitのスレーブアドレス(B0111110)と、
// 1bitのR/Wビット（今回、WriteOnlyなのでずっと0)を送信
// B0111110 + 0 = 0x7C
// ②コントロールバイト(8bit)として、
// 1bitの"Co" 連続データ = 1, 最終データ = 0
// 1bitの"RS" "コマンド" = 0, "データ" = 1
// 6bitの"0"(B000000)
// を送信
// ③その後、7bitのデータを送信する

void LCDInitialize(void) {
    uint8_t l_commandTable[10] = {0x38, 0x39, 0x14, 0x70, 0x52, 0x6C, 0x38, 0x0C, 0x01};
    uint8_t c;

    // 40ms以上待つ
    __delay_ms(40);

    for (c = 0; c < 10; c++) {
        // コマンドを送信
        I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, l_commandTable[c]);
        if (c == 5) {
            __delay_ms(200);
        } else {
            // 26.3us以上待つ
            __delay_us(27);
        }
    }

    // 1.08ms以上 待つ
    __delay_ms(2);
}

// LCD上の書き込む場所を指定

inline void SetPosLCD(uint8_t i_pos) {
    // Set DDRAM address DB7 = 1
    // 設定可能ビット DB0 ~ DB6

    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, (LCD_SET_POS_DB7 | i_pos));
}

// LCD上の書き込む場所を、
// 上の行か下の行の先頭を指定する
// true だと 2行目
// false だと 1行目

inline void SetPosLineLCD(bool i_row) {
    if (i_row) {
        // true 2行目
        I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, (LCD_SET_POS_DB7 | LINE_SECOND_ADDR));
    } else {
        // false 1行目
        I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, (LCD_SET_POS_DB7 | LINE_FIRST_ADDR));
    }
}

// WriteToBuffer

void WriteToBuffer(uint8_t *i_str, uint8_t i_strLen) {
    uint8_t i;

    for (i = 0; i < i_strLen; i++) {
        LCDBuffer[i] = i_str[i];
    }
}

// BufferToWrite

void BufferToLCD(void) {
    SetPosLineLCD(0);
    Write1LineToLCD(LCDBuffer, 8);
    SetPosLineLCD(1);
    Write1LineToLCD(&LCDBuffer[8], 8);
}

// Write1LineToLCD()
// 説明：現在のアドレスに1 ～ 8 文字分の文字を書く
// 引数:
// 　i_str は、8文字分の表示させた文字列が入った
// 　uint8_t型の配列

void Write1LineToLCD(uint8_t *i_str, uint8_t i_len) {
    // MAX_BUF_SIZE = 9
    uint8_t l_buf[MAX_BUF_SIZE];
    uint8_t *str_error = "error";
    uint8_t c;

    l_buf[0] = WR_CONTROLE_BYTE;

    // もし、8文字より多い文字数が入った場合、
    if (i_len > LINE_DIGITS_MAX) {
        // errorを表示
        for (c = 1; c <= i_len; c++) {
            l_buf[c] = str_error[c - 1];
        }
        I2C1_WriteNBytes(LCD_ADDR, str_error, 6);

    } else {
        for (c = 1; c <= i_len; c++) {
            l_buf[c] = i_str[c - 1];
        }

        I2C1_WriteNBytes(LCD_ADDR, l_buf, ++i_len);
    }
}

// ClearDisplay

void ClrLineDisplay(uint8_t i_line) {
    SetPosLCD(i_line);
    Write1LineToLCD(str_blank, 8);
}

void ClrDisplay(void) {
    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_LCD_CLR_DISPLAY);
}

inline void SetLCDResetFlg(void) {
    LCDResetFlg = ON;
}

// inline void ClrLCDResetFlg(void) { LCDResetFLg = OFF; }

// Display ON

void DisplayON(void) {
    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_LCD_DISPLAY_ON);
}
// Display OFF

void DisplayOFF(void) {
    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_LCD_DISPLAY_OFF);
}
