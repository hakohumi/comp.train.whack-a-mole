/*
SE

SEを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ



 */

#include "SE.h"

#include "Buzzer.h"
#include "SheetMusic.h"
#include "tmr2.h"

// LEDでデバッグするため
#include "LED.h"
// LCDでデバッグするため
#include "LCD.h"

/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */

// SE楽譜が入るポインタ変数
static SheetMusic_t *SE_SheetMusic;

/* -------------------------------------------------- */
// SE
/* -------------------------------------------------- */

// SEの再生位置
static uint16_t SE_PlayNotePos = 0;
// SEの終端位置
static uint16_t SE_EndPos = 0;
// 音符中の再生位置
static uint16_t currentNoteLength = 0;
// SE再生中フラグ
static bool IsPlaySE   = OFF;
static bool SEStartFlg = OFF;
static bool SEStopFlg  = OFF;

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */
/* -------------------------------------------------- */

// ブザーの初期化

void SE_Initialize(void) {
    // SEの楽譜に、ドレミを指定
    SheetMusic_Initialize(&SE_SheetMusic, SM_SE_DOREMI);
    // 楽譜の最後の位置を記録
    SE_EndPos = SM_GetMaxNotes(SE_SheetMusic);
}

// BGM再生開始フラグのON
void PlaySE(void) {
    SEStartFlg = ON;
}

/* -------------------------------------------------- */
// SE頭出し処理

/* -------------------------------------------------- */

void SE_returnBeginPlayPos(void) {
    uint8_t l_NoteTempo  = SM_GetTempo(SE_SheetMusic);
    uint8_t l_NoteLength = *(SM_GetCurrentNote(SE_SheetMusic, 0));

    // 選択された音符の長さをcurrentNoteLengthにセットする
    currentNoteLength = Change10msLength(l_NoteLength, l_NoteTempo);

    // 音符の高さに合わせて、タイマの周期を変える
    SM_ChangePich(SE_SheetMusic, 0);
}

// SEStateの切り替え
void SE_updateState(void) {
    // SE再生フラグが立ったか？
    // SEStartFlg
    if (SEStartFlg == ON) {
        // SEStartFlgを下げる
        SEStartFlg = OFF;

        // 現在再生されているか
        if (IsPlaySE == ON) {
            // SEのcurrentNotePosを最初の位置へクリア
            SE_returnBeginPlayPos();
        } else {
            // IsPlaySEをtrueに変更する
            IsPlaySE = true;

            // 最初の処理
            SE_returnBeginPlayPos();

            // PWM開始
            PlayBuzzer();
        }
    }

    // SE停止フラグが立ったか?
    // SEStopFlg
    if (SEStopFlg == ON) {
        // SEStopFlgを下げる
        SEStopFlg = OFF;

        // IsPlaySEをfalseに変更する
        IsPlaySE = false;

        // ブザーの音程をBGMの現在の再生位置の音程へ設定する
        BGM_ChangeCurrentPich();

        // // PWMを停止させる
        // TMR2_StopTimer();
    }
}

// SEの更新
uint8_t l_str[8];

void SE_updateManager(void) {
    uint8_t l_NoteTempo  = 0;
    uint8_t l_NoteLength = 0;

    // 現在SEが再生されているか
    if (IsPlaySE == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (currentNoteLength == 0) {
            // currentBGMNotePosを1増やす
            SE_PlayNotePos++;

            // SEの再生位置は終端か？
            if (SE_PlayNotePos >= SE_EndPos) {
                // BGMの再生位置を最初へ戻す
                SE_PlayNotePos = 0;

                // SEの再生状態をOFFにする
                SEStopFlg = ON;
            } else {
                l_NoteLength =
                    *(SM_GetCurrentNote(SE_SheetMusic, SE_PlayNotePos));
                l_NoteTempo = SM_GetTempo(SE_SheetMusic);
                // 選択された音符の長さをcurrentNoteLengthにセットする
                currentNoteLength = Change10msLength(l_NoteLength, l_NoteTempo);

                // ブザーの周波数を、現在の再生位置の音程へ変更する
                SM_ChangePich(SE_SheetMusic, SE_PlayNotePos);
            }
        } else {
            // currentNoteLengthを1下げる
            currentNoteLength--;
        }
        // デバッグ用
        // currentNoteLengthをLEDで表示
        UpdateLED(*(SM_GetCurrentNote(SE_SheetMusic, SE_PlayNotePos)));

        ItoStr(currentNoteLength, l_str, 8);
        WriteToBufferFirst(l_str, 8);
    }
}

/* -------------------------------------------------- */
// ゲッター

/* -------------------------------------------------- */

bool GetIsPlaySE() {
    return IsPlaySE;
}
