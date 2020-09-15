/*
BGM

BGMを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ

 */

#include "BGM_MusicSheets.h"
#include "Buzzer.h"
#include "tmr2.h"
// LEDでデバッグするため
#include "LED.h"

// SEが再生中かどうかを確認するため
#include "SE.h"

/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// BGM
/* -------------------------------------------------- */

// BGMの再生位置
static uint16_t BGMPlayNotePos = 0;
// BGMの終端位置
static uint16_t BGMEndPos = 0;

// 音符中の再生位置
static uint16_t BGM_currentNoteLength = 0;

// BGM再生中フラグ
static bool IsPlayBGM = OFF;
// BGM再生開始フラグ
static bool BGMStartFlg = OFF;
// BGM停止開始フラグ
static bool BGMStopFlg = OFF;
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */
/* -------------------------------------------------- */

// BGMの初期化

void BGM_Initialize(void) {
    // 楽譜の最後の位置を記録
    BGMEndPos = GetBGMMaxNotes();
}

// BGM再生開始フラグのON

void PlayBGM(void) {
    BGMStartFlg = ON;
}

// BGM頭出し処理

void BGM_returnBeginPlayPos(void) {
    uint8_t l_pich = 0;

    // 選択された音符の長さをcurrentNoteLengthにセットする
    BGM_currentNoteLength = Change1msLength(*(GetBGMCurrentNote(0)), GetBGMTempo());

    // 音符の高さに合わせて、タイマの周期を変える
    l_pich = GetBGMCurrentNotePich(0);
    ChangePich(l_pich);
}

// BGMStateの切り替え

void updateBGMState(void) {
    // BGM再生フラグが立ったか？
    // BGMStartFlg
    if (BGMStartFlg == ON) {
        // BGMStartFlgを下げる
        BGMStartFlg = OFF;

        // IsPlayBGMをtrueに変更する
        IsPlayBGM = true;

        // 最初の処理
        BGM_returnBeginPlayPos();

        // PWM開始
        PlayBuzzer();
    }

    // BGM停止フラグが立ったか?
    // BGMStopFlg
    if (BGMStopFlg == ON) {
        // BGMStopFlgを下げる
        BGMStopFlg = OFF;

        //IsPlayBGMをfalseに変更する
        IsPlayBGM = false;

        // // PWMを停止させる
        // TMR2_StopTimer();
    }
}

// BGMの更新

void updateBGMManager(void) {
    uint8_t l_pich = 0;

    // 現在BGMが再生されているか
    if (IsPlayBGM == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (BGM_currentNoteLength == 0) {
            // currentBGMNotePosを1増やす
            BGMPlayNotePos++;

            // BGMの再生位置は終端か？
            if (BGMPlayNotePos >= BGMEndPos) {
                // BGMの再生位置を最初へ戻す
                BGMPlayNotePos = 0;
            }

            //BGMが再生中に効果音が再生していたら、
            if (SE_GetIsPlay() == OFF) {
                // 選択された音符の長さをcurrentNoteLengthにセットする
                BGM_currentNoteLength = Change1msLength(*(GetBGMCurrentNote(BGMPlayNotePos)), GetBGMTempo());
                // 音符の高さに合わせて、タイマの周期を変える
                // 音の高さを取得する
                l_pich = GetBGMCurrentNotePich(BGMPlayNotePos);
                // 音の高さに合わせて、タイマの周期とデューティー比を変更
                ChangePich(l_pich);
            }

        } else {
            // currentNoteLengthを1下げる
            BGM_currentNoteLength--;
        }

        // デバッグ用
        // currentNoteLengthをLEDで表示
        // UpdateLED(currentNoteLength);
    }
}

// BGMの再生位置を取得

uint16_t GetBGMPlayPos(void) {
    return BGMPlayNotePos;
}

/* -------------------------------------------------- */
// ゲッター

/* -------------------------------------------------- */
bool GetIsPlayBGM() {
    return IsPlayBGM;
}
