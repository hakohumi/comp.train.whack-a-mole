/*
Buzzer

BGMとSEを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ



*/

#include "Buzzer.h"

#include "MusicSheets.h"
#include "tmr2.h"

#define NOTE_LENGTH 0
#define NOTE_PITCH 1

/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

static uint8_t PichTable[8] = {
    0x92,
    0x82,
    0x74,
    0x6D,
    0x61,
    0x56,
    0x4D,
    0x49}

static bool LengthNote16thFlg     = OFF;
static uint16_t LengthNote16th_ms = 0;

// BGMの再生位置
static uint16_t BGMPlayPos = 0;
// BGMの終端位置
static uint16_t BGMEndPos = 0;

// 音符中の再生位置
static uint8_t currentNoteLength = 0;
// BGM再生中フラグ
static bool IsPlayBGM = OFF;
// SE再生中フラグ
static bool IsPlaySE = OFF;

// ブザーの初期化

void Buzzer_Initialize(void) {
    uint8_t Tempo = 0;

    // BGMの楽譜のテンポを取得する
    Tempo = GetBGMTempo();

    // 16分音符の長さを計算する
    // LengthNote16th_ms = 15 * 1000 / テンポ = 16分音符の長さ(ms)
    LengthNote16th_ms = 15000 / Tempo;

    LengthNote16thFlg = ON;
}

// ブザーの更新

void UpdateBuzzer(void) {
    // BGMStateの切り替え
    // SEStateの切り替え
    // LengthNote16thフラグ
    if (LengthNote16thFlg == ON) {
        // BGMManagerを更新
        UpdateBGMManager();
        // SEManagerを更新
        UpdateSEManager();
        // LengthNote16thFlgを下げる
        LengthNote16thFlg = OFF;
    }
}

// BGMの更新
void UpdateBGMManager(void) {
    // 現在BGMが再生されているか
    if (IsPlayBGM == ON) {
        // BGMの再生位置は終端か？
        if (BGMNotePos >= BGMEndPos) {
            // BGMの再生位置を最初へ戻す
            BGMNotePos = 0;
        }

        // 現在選択されている音符の長さ分の時間は経過したか？
        if (currentNoteLength <= 0) {
            // currentBGMNotePosを1増やす
            BGMNotePos++;
            // 選択された音符の長さをcurrentNoteLengthにセットする
            currentNoteLength = GetBGMCurrentNoteLength(BGMNotePos);

            // 音符の高さに合わせて、タイマの周期を変える
            TMR2_LoadPeriodRegister(PichTable[GetBGMCurrentNotePich(BGMNotePos)]);
        } else {
            // currentNoteLengthを1下げる
            currentNoteLength--;
        }
    }
}

// SEの更新

void UpdateSEManager(void) {
}

// BGMの再生位置を取得
uint16_t GetBGMPlayPos(void) {
    return BGMPlayPos;
}

void Buzzer_SetLengthNote16thFlg(void) {
    LengthNote16thFlg = ON;
}