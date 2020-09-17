
#include "LCD.h"

#include <mcc.h>
#include <string.h>

#include "Common.h"
#include "examples/i2c1_master_example.h"
// モグラの状態用
#include "_Mole.h"

/* -------------------------------------------------- */
// プライベートなdefine
/* -------------------------------------------------- */
/* -------------------------------------------------- */
// I2Cコマンド用
/* -------------------------------------------------- */

// Co = 0, RS = 0, Control byte = 0;
#define CONTROLE_BYTE (uint8_t)(0x00)
// RSビットが立っているとき
#define WR_CONTROLE_BYTE (uint8_t)(0x40)

// LCDのSETPOSをするために立てるビット
#define LCD_SET_POS_DB7 0x80

// ファンクションセットをするコマンド
#define CMD_FUNCTION_SET_IS_ON 0x39
#define CMD_FUNCTION_SET_IS_OFF 0x38
// Set CGRAM
// 0 1 AC5 AC4 AC3 AC2 AC1 AC0
#define CMD_SET_CGRAM 0x40

// ClearDisplay コマンドのデータ部
#define CMD_LCD_CLR_DISPLAY 0x01

// Display ON コマンドのデータ部
#define CMD_LCD_DISPLAY_ON 0x0C

// Display OFF コマンドのデータ部
#define CMD_LCD_DISPLAY_OFF 0x08
/* -------------------------------------------------- */

// LCDに書き込む文字列保存用バッファ 16文字
#define LCD_BUFF_SIZE_MAX 17
// 1行の8文字表示用バッファ
#define BUFF_LINE_SIZE_MAX 9
// 1行の表示可能桁数
#define LINE_DIGITS_MAX 8

// LCDの行頭のアドレス
#define LINE_FIRST_ADDR 0x00
#define LINE_SECOND_ADDR 0x40

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

static uint8_t LCDBuffer[LCD_BUFF_SIZE_MAX];

// LCD更新フラグ
// バッファに書き込んだ時のみONになる
static bool updateLCDFlg = OFF;
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// グローバル変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */

// 1行書き込む
static void write1LineToLCD(uint8_t *i_str, uint8_t i_len);

// LCD更新フラグをONにする
#define setUpdateLCDFlg()  \
    do {                   \
        updateLCDFlg = ON; \
    } while (0)

// モグラの絵をLCDのCGRAMに書き込む
static void createMoleGpaph(void);

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
    uint8_t l_commandTable[10] = {
        CMD_FUNCTION_SET_IS_OFF, CMD_FUNCTION_SET_IS_ON, 0x14, 0x70, 0x52, 0x6C, CMD_FUNCTION_SET_IS_OFF, 0x0C, 0x01

    };
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

    // LCDの初期化コマンド
    ClrDisplay();

    // LCDBuffer変数の初期化
    memset(LCDBuffer, '\0', sizeof(LCDBuffer) / sizeof(char));

    // モグラの絵をLCDのCGRAMに書き込む
    createMoleGpaph();
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
// 引数
// 　i_strLen 文字列の文字数。終端文字はカウントしない

void WriteToBuffer(uint8_t *i_str, uint8_t i_strLen) {
    uint8_t i;

    setUpdateLCDFlg();

    // もし、指定された文字数が16を超えていたら、
    if (i_strLen > 16) {
        // エラー
        ErrorToBuffer(ERR_W_T_B_OVERSTRLEN);
    } else {
        // LCDBufferに空白を入れる
        strncpy(LCDBuffer, *STR_2LINE_BLANK, LCD_BUFF_SIZE_MAX);

        // LCDBufferの先頭から、引数に指定された文字列をコピーする
        for (i = 0; i < i_strLen; i++) {
            LCDBuffer[i] = i_str[i];
        }
    }
}

void WriteToBufferFirst(uint8_t *i_str, uint8_t i_strLen) {
    uint8_t i;

    setUpdateLCDFlg();

    // もし、指定された文字数が8を超えていたら、
    if (i_strLen > 8) {
        // エラー
        ErrorToBuffer(ERR_W_T_B_F_OVERSTRLEN);
    } else {
        // LCDBufferの上の行に空白を入れる
        strncpy(LCDBuffer, STR_LINE_BLANK, LCD_LINE_LEN);

        // LCDBufferの先頭から、引数に指定された文字列をコピーする
        for (i = 0; i < i_strLen; i++) {
            LCDBuffer[i] = i_str[i];
        }
    }
}

void WriteToBufferSecond(uint8_t *i_str, uint8_t i_strLen) {
    uint8_t i;

    // LCD更新フラグをONにする
    setUpdateLCDFlg();

    // もし、指定された文字数が8を超えていたら、
    if (i_strLen > 8) {
        // エラー
        ErrorToBuffer(ERR_W_T_B_S_OVERSTRLEN);
    } else {
        // LCDBufferの下の行に空白を入れる
        strncpy(&LCDBuffer[8], STR_LINE_BLANK, LCD_LINE_LEN);

        // LCDBufferの先頭から、引数に指定された文字列をコピーする
        for (i = 0; i < i_strLen; i++) {
            LCDBuffer[i + LCD_LINE_LEN] = i_str[i];
        }
    }
}

// ゲーム中に、残り時間を変更した時に呼ばれる
// 残り時間の位置のバッファを書き換える
// 引数 uint8_t i_time 残り制限時間 0 ~ 60

void WriteToBufferTime(uint8_t i_time) {
    // LCD更新フラグをONにする
    setUpdateLCDFlg();

    // 1の位を格納
    LCDBuffer[7] = itochar((uint8_t)(i_time % 10));
    // 桁をずらす
    i_time /= 10;
    // 10の位を格納
    LCDBuffer[6] = itochar((uint8_t)(i_time % 10));
}
// ゲーム中に、スコアを変更した時に呼ばれる
// スコアの位置のバッファを書き換える
// 引数 uint8_t i_score 0 ~ 999

void WriteToBufferScore(uint16_t i_score) {
    // LCD更新フラグをONにする
    setUpdateLCDFlg();

    // 1の位を格納
    LCDBuffer[3] = itochar((uint8_t)(i_score % 10));
    // 桁をずらす
    i_score /= 10;
    // 10の位を格納
    LCDBuffer[2] = itochar((uint8_t)(i_score % 10));
    // 桁をずらす
    i_score /= 10;
    // 100の位を格納
    LCDBuffer[1] = itochar((uint8_t)(i_score % 10));
}

/* -------------------------------------------------- */
// モグラの表示に関連する
/* -------------------------------------------------- */
#define MOLE_LCD_POS_1 9
#define MOLE_LCD_POS_2 11
#define MOLE_LCD_POS_3 13
#define MOLE_LCD_POS_4 15
#define MOLE_GPAPH_HOLE_ADDR 0x01
#define MOLE_GPAPH_MOLE_ADDR 0x02
#define MOLE_GPAPH_HIT_ADDR 0x03

// モグラの絵を切り替える
// 入力 切り替えるモグラの位置、切り替えるモグラの状態
// とりあえず今は文字の表示

void WriteToBufferMole(uint8_t i_molePos, uint8_t i_moleState) {
    uint8_t l_molePos = 99;
    uint8_t l_str[1];
    // LCD更新フラグをONにする
    setUpdateLCDFlg();

    switch (i_molePos) {
        case 1:
            l_molePos = MOLE_LCD_POS_1;
            break;
        case 2:
            l_molePos = MOLE_LCD_POS_2;
            break;
        case 3:
            l_molePos = MOLE_LCD_POS_3;
            break;
        case 4:
            l_molePos = MOLE_LCD_POS_4;
            break;
        default:
            // 到達不可
            break;
    }
    switch (i_moleState) {
        case HOLE:
            *l_str = MOLE_GPAPH_HOLE_ADDR;
            break;
        case MOLE:
            *l_str = MOLE_GPAPH_MOLE_ADDR;
            break;
        case HIT:
            *l_str = MOLE_GPAPH_HIT_ADDR;
            break;
        default:
            // 到達不可
            *l_str = 'E';
            break;
    }

    LCDBuffer[l_molePos] = *l_str;
}

static const uint8_t grapMoleHOLE_CG[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00001110,
    0b00011111,
    0b00001110

};
static const uint8_t grapMoleMOLE_CG[8] = {
    0b00000000,
    0b00001110,
    0b00010001,
    0b00011011,
    0b00010101,
    0b00010001,
    0b00010001,
    0b00001110

};
static const uint8_t grapMoleHIT_CG[8] = {
    0b00001100,
    0b00001111,
    0b00001100,
    0b00000000,
    0b00001110,
    0b00010001,
    0b00011011,
    0b00010101

};

static void createMoleGpaph(void) {
    uint8_t c;

    // データを書き込む
    for (c = 0; c < 8; c++) {
        // T
        I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_SET_CGRAM | 1 << 3 | (c));
        I2C1_Write1ByteRegister(LCD_ADDR, WR_CONTROLE_BYTE, grapMoleHOLE_CG[c]);
    }
    // データを書き込む
    for (c = 0; c < 8; c++) {
        // T
        I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_SET_CGRAM | 2 << 3 | (c));
        I2C1_Write1ByteRegister(LCD_ADDR, WR_CONTROLE_BYTE, grapMoleMOLE_CG[c]);
    }
    // データを書き込む
    for (c = 0; c < 8; c++) {
        // T
        I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_SET_CGRAM | 3 << 3 | (c));
        I2C1_Write1ByteRegister(LCD_ADDR, WR_CONTROLE_BYTE, grapMoleHIT_CG[c]);
    }
}

/* -------------------------------------------------- */

// BufferToLCD

void BufferToLCD(void) {
    // バッファに変更があった時のみ更新する
    if (updateLCDFlg == ON) {
        updateLCDFlg = OFF;
        SetPosLineLCD(0);
        write1LineToLCD(LCDBuffer, 8);
        SetPosLineLCD(1);
        write1LineToLCD(&LCDBuffer[8], 8);
    }
}

// errorをBufferに保存

void ErrorToBuffer(uint8_t num) {
    uint8_t i, l_len;

    for (i = 0, l_len = STR_ERROR_LEN + 1; i < l_len; i++) {
        LCDBuffer[i] = STR_ERROR[i];
    }

    // エラー番号を2行の最初に表記
    ItoStr(num, &LCDBuffer[8], 2);
}

// ClearDisplay

void ClrLineDisplay(uint8_t i_line) {
    SetPosLCD(i_line);
    write1LineToLCD(STR_LINE_BLANK, 8);
}

void ClrDisplay(void) {
    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_LCD_CLR_DISPLAY);
}

// Display ON

void DisplayON(void) {
    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_LCD_DISPLAY_ON);
}
// Display OFF

void DisplayOFF(void) {
    I2C1_Write1ByteRegister(LCD_ADDR, CONTROLE_BYTE, CMD_LCD_DISPLAY_OFF);
}

// Write1LineToLCD()
// 説明：現在のアドレスに1 ～ 8 文字分の文字を書く
// 引数:
// 　i_str は、8文字分の表示させた文字列が入った
// 　uint8_t型の配列
// 　終端文字はなし

static void write1LineToLCD(uint8_t *i_str, uint8_t i_len) {
    // 先頭のコントロールバイト分と文字数の最大値8の
    // 合計9バイトを確保する
    // BUFF_LINE_SIZE_MAX = 9
    uint8_t l_buf[BUFF_LINE_SIZE_MAX];
    uint8_t c;

    // l_bufの初期化
    memset(l_buf, '\0', BUFF_LINE_SIZE_MAX);

    l_buf[0] = WR_CONTROLE_BYTE;

    // もし、8文字より多い文字数が入った場合、
    if (i_len > LINE_DIGITS_MAX) {
        // errorを表示
        for (c = 1; c <= 6; c++) {
            l_buf[c] = STR_ERROR[c - 1];
        }
        // 文字列"ERROR"の数
        i_len = STR_ERROR_LEN;

    } else {
        for (c = 1; c <= i_len; c++) {
            l_buf[c] = i_str[c - 1];
        }
    }

    // 書き込み
    // +1 は先頭のコントロールバイト分
    I2C1_WriteNBytes(LCD_ADDR, l_buf, i_len + 1);
}
