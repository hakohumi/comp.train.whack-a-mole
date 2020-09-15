/*
Buzzer

BGMとSEを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ



 */

#include "Buzzer.h"

#include "BGM.h"
#include "SE.h"
#include "tmr2.h"
// PWMのデューティ比を変更するため
#include "BGM_MusicSheets.h"
#include "pwm3.h"
/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

// 音程テープル
uint8_t PichTable[SCALE_NUM] = {
    0x00,  // REST

    0xEE,  // DO
    0xE1,  // DO_SHARP
    0xD4,  // RE
    0xC8,  // RE_SHARP
    0xBD,  // MI
    0xB2,  // FA
    0xA8,  // FA_SHARP
    0x9F,  // SO
    0x96,  // SO_SHARP
    0x8E,  // RA
    0x86,  // RA_SHARP
    0x7E,  // SI
    0x77,  // DO2
    0x6A,  // RE2
    0x5E,  // MI2
    0x59,  // FA2
    0x4F,  // SO2
    0x47,  // RA2
    0x3F   // SI2

};

static uint16_t LengthNote16th_ms = 0;

static bool LengthNote16thFlg  = OFF;
static bool Update1msBuzzerFlg = OFF;

static bool IsPlayingBuzzer = OFF;

// ブザーの初期化

void Buzzer_Initialize(void) {
    uint16_t Tempo = 0;
    uint8_t l_pich = 0;

    // BGMの楽譜のテンポを取得する
    Tempo = GetBGMTempo();

    // 16分音符の長さを計算する
    // LengthNote16th_ms = 15 * 1000 / テンポ = 16分音符の長さ(ms)
    LengthNote16th_ms = 15000 / Tempo;

    BGM_Initialize();
    SE_Initialize();
}

// ブザーの更新

void UpdateBuzzer(void) {
    // BGMStateの切り替え
    updateBGMState();
    // SEStateの切り替え
    SE_updateState();

    // どっちも再生中でなければ、PWMをストップさせる
    if ((GetIsPlayBGM() || SE_GetIsPlay()) == OFF) {
        IsPlayingBuzzer = OFF;
        TMR2_StopTimer();
    }

    // // LengthNote16thフラグ
    // if (LengthNote16thFlg == ON) {
    //     // BGMManagerを更新
    //     updateBGMManager();
    //     // SEManagerを更新
    //     SE_updateManager();
    //     // LengthNote16thFlgを下げる
    //     LengthNote16thFlg = OFF;
    // }

    // 1msフラグ
    if (Update1msBuzzerFlg == ON) {
        // BGMManagerを更新
        updateBGMManager();
        // SEManagerを更新
        SE_updateManager();
        // LengthNote16thFlgを下げる
        Update1msBuzzerFlg = OFF;
    }
}

// PWMを開始する
void PlayBuzzer(void) {
    if (IsPlayingBuzzer == OFF) {
        TMR2_StartTimer();
        IsPlayingBuzzer = ON;
    }
}

void Buzzer_SetLengthNote16thFlg(void) {
    LengthNote16thFlg = ON;
}

// 音程の変更
// タイマの周期とデューティー比を変更

void ChangePich(uint8_t i_Pich) {
    uint8_t l_Pich = PichTable[i_Pich];

    if (l_Pich != 0) {
        // タイマに書き込み
        TMR2_LoadPeriodRegister(l_Pich);
        // PWMのデューティー比を50%になるように変更
        PWM3_LoadDutyValue(l_Pich / 2);
    } else {
        // PWMのデューティー比を0%になるように変更
        PWM3_LoadDutyValue(0);
    }
}

// 音符の長さを1msに変換
// 入力は16分音符の個数とテンポ
// 出力はmsか

uint16_t Change1msLength(uint8_t i_NoteLength, uint16_t i_Tempo) {
    // LengthNote16th_ms = 15 * 1000 / テンポ = 16分音符の長さ(ms)
    return ((15000 / i_Tempo) * i_NoteLength);
}

uint16_t GetLengthNote16th_ms(void) {
    return LengthNote16th_ms;
}

void SetUpdate1msBuzzerFlg(void) {
    Update1msBuzzerFlg = ON;
}