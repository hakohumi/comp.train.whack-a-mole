/*
Buzzer

BGMとSEを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ



 */

#include "Buzzer.h"

#include "BGM_MusicSheets.h"
#include "tmr2.h"
// PWMのデューティ比を変更するため
#include "pwm3.h"

// LEDでデバッグするため
#include "LED.h"

#define NOTE_LENGTH 0
#define NOTE_PITCH 1

/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

// 音程テープル
static uint8_t PichTable[SCALE_NUM] = {
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

static bool LengthNote16thFlg     = OFF;
static uint16_t LengthNote16th_ms = 0;

// BGMの再生位置
static uint16_t BGMPlayNotePos = 0;
// BGMの終端位置
static uint16_t BGMEndPos = 0;

// 音符中の再生位置
static uint8_t currentNoteLength = 0;
// BGM再生中フラグ
static bool IsPlayBGM = OFF;
// BGM再生開始フラグ
static bool BGMStartFlg = OFF;
// BGM停止開始フラグ
static bool BGMStopFlg = OFF;

// SE再生中フラグ
static bool IsPlaySE = OFF;

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */

static void updateBGMManager(void);
static void updateBGMState(void);
static void updateSEManager(void);
static void changePich(uint8_t i_Pich);
static void returnBeginPlayPos(void);
/* -------------------------------------------------- */

// ブザーの初期化

void Buzzer_Initialize(void) {
    uint16_t Tempo = 0;
    uint8_t l_pich = 0;

    // BGMの楽譜のテンポを取得する
    Tempo = GetBGMTempo();

    // 16分音符の長さを計算する
    // LengthNote16th_ms = 15 * 1000 / テンポ = 16分音符の長さ(ms)
    LengthNote16th_ms = 15000 / Tempo;

    // 楽譜の最後の位置を記録
    BGMEndPos = GetBGMMaxNotes();
}

// BGM再生開始フラグのON

void PlayBGM(void) {
    BGMStartFlg = ON;
}

// ブザーの更新

void UpdateBuzzer(void) {
    // BGMStateの切り替え
    updateBGMState();
    // SEStateの切り替え

    // LengthNote16thフラグ
    if (LengthNote16thFlg == ON) {
        // BGMManagerを更新
        updateBGMManager();
        // SEManagerを更新
        updateSEManager();
        // LengthNote16thFlgを下げる
        LengthNote16thFlg = OFF;
    }
}

// BGM頭出し処理

static void returnBeginPlayPos(void) {
    uint8_t l_pich = 0;

    // 選択された音符の長さをcurrentNoteLengthにセットする
    currentNoteLength = *(GetBGMCurrentNote(0));

    // 音符の高さに合わせて、タイマの周期を変える
    l_pich = GetBGMCurrentNotePich(0);
    changePich(l_pich);
}

static void updateBGMState(void) {
    // BGM再生フラグが立ったか？
    // BGMStartFlg
    if (BGMStartFlg == ON) {
        // BGMStartFlgを下げる
        BGMStartFlg = OFF;
        // IsPlayBGMをtrueに変更する
        IsPlayBGM = true;

        // 最初の処理
        returnBeginPlayPos();

        // PWMを開始させる
        TMR2_StartTimer();
    }

    // BGM停止フラグが立ったか?
    // BGMStopFlg
    if (BGMStopFlg == ON) {
        // BGMStopFlgを下げる
        BGMStopFlg = OFF;

        //IsPlayBGMをfalseに変更する
        IsPlayBGM = false;
        // PWMを停止させる
        TMR2_StopTimer();
    }
}

// BGMの更新

static void updateBGMManager(void) {
    uint8_t l_pich = 0;

    // 現在BGMが再生されているか
    if (IsPlayBGM == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (currentNoteLength == 0) {
            // currentBGMNotePosを1増やす
            BGMPlayNotePos++;

            // BGMの再生位置は終端か？
            if (BGMPlayNotePos >= BGMEndPos) {
                // BGMの再生位置を最初へ戻す
                BGMPlayNotePos = 0;
            }

            // 選択された音符の長さをcurrentNoteLengthにセットする
            currentNoteLength = *(GetBGMCurrentNote(BGMPlayNotePos));
            // 音符の高さに合わせて、タイマの周期を変える
            // 音の高さを取得する
            l_pich = GetBGMCurrentNotePich(BGMPlayNotePos);
            // 音の高さに合わせて、タイマの周期とデューティー比を変更
            changePich(l_pich);

        } else {
            // currentNoteLengthを1下げる
            currentNoteLength--;
        }

        // デバッグ用
        // currentNoteLengthをLEDで表示
        UpdateLED(currentNoteLength);
    }
}

// SEの更新

static void updateSEManager(void) {
}

// BGMの再生位置を取得

uint16_t GetBGMPlayPos(void) {
    return BGMPlayNotePos;
}

void Buzzer_SetLengthNote16thFlg(void) {
    LengthNote16thFlg = ON;
}

// 音程の変更
// タイマの周期とデューティー比を変更

static void changePich(uint8_t i_Pich) {
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

/* -------------------------------------------------- */
// ゲッター

/* -------------------------------------------------- */
bool GetIsPlayBGM() {
    return IsPlayBGM;
}

bool GetIsPlaySE() {
    return IsPlaySE;
}

uint16_t GetLengthNote16th_ms() {
    return LengthNote16th_ms;
}