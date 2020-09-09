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

// 音程テープル
static uint8_t PichTable[8] = {

    0x92,
    0x82,
    0x74,
    0x6D,
    0x61,
    0x56,
    0x4D,
    0x49

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
/* -------------------------------------------------- */

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

static void updateBGMState(void) {
    // BGM再生フラグが立ったか？
    // BGMStartFlg
    if (BGMStartFlg == ON) {
        // BGMStartFlgを下げる
        BGMStartFlg = OFF;
        // IsPlayBGMをtrueに変更する
        IsPlayBGM = true;

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
    // 現在BGMが再生されているか
    if (IsPlayBGM == ON) {
        // BGMの再生位置は終端か？
        if (BGMPlayNotePos >= BGMEndPos) {
            // BGMの再生位置を最初へ戻す
            BGMPlayNotePos = 0;
        }

        // 現在選択されている音符の長さ分の時間は経過したか？
        if (currentNoteLength <= 0) {
            // currentBGMNotePosを1増やす
            BGMPlayNotePos++;
            // 選択された音符の長さをcurrentNoteLengthにセットする
            currentNoteLength = GetBGMCurrentNoteLength(BGMPlayNotePos);

            // 音符の高さに合わせて、タイマの周期を変える
            TMR2_LoadPeriodRegister(PichTable[GetBGMCurrentNotePich(BGMPlayNotePos)]);
        } else {
            // currentNoteLengthを1下げる
            currentNoteLength--;
        }
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