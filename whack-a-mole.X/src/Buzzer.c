#include "Buzzer.h"

#include "MusicSheets.h"

#define NOTE_LENGTH 0
#define NOTE_PITCH 1

static bool LengthNote16thFlg = OFF;

// ブザーの初期化

void Buzzer_Initialize(void) {
    // BGMの楽譜のテンポを取得する

    // 16分音符の長さを計算する
    // LengthNote16th = 15/テンポ

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
}

// SEの更新

void UpdateSEManager(void) {
}