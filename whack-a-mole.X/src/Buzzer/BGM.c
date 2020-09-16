/*
BGM

BGMを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ

 */

#include "BGM.h"

#include "Buzzer.h"
#include "SheetMusic.h"
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

// BGM楽譜が入るポインタ変数
static SheetMusic_t *BGM_SheetMusic;

/* -------------------------------------------------- */
// BGM
/* -------------------------------------------------- */

// BGMの再生位置
static uint16_t BGM_PlayNotePos = 0;
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
    // BGMの楽譜に、ドレミを指定
    SheetMusic_Initialize(&BGM_SheetMusic, SM_BGM_DOREMI);
    // 楽譜の最後の位置を記録
    BGMEndPos = SM_GetMaxNotes(BGM_SheetMusic);
}

// BGM再生開始フラグのON

void PlayBGM(void) {
    BGMStartFlg = ON;
}

/* -------------------------------------------------- */
// BGM頭出し処理

/* -------------------------------------------------- */

void BGM_returnBeginPlayPos(void) {
    uint8_t l_NoteTempo  = SM_GetTempo(BGM_SheetMusic);
    uint8_t l_NoteLength = *(SM_GetCurrentNote(BGM_SheetMusic, 0));

    // 選択された音符の長さをcurrentNoteLengthにセットする
    BGM_currentNoteLength = Change10msLength(l_NoteLength, l_NoteTempo);

    // 音符の高さに合わせて、タイマの周期を変える
    SM_ChangePich(BGM_SheetMusic, 0);
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

        // IsPlayBGMをfalseに変更する
        IsPlayBGM = false;

        // // PWMを停止させる
        // TMR2_StopTimer();
    }
}

// BGMの更新

void updateBGMManager(void) {
    uint8_t l_NoteTempo  = 0;
    uint8_t l_NoteLength = 0;

    // 現在BGMが再生されているか
    if (IsPlayBGM == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (BGM_currentNoteLength == 0) {
            // currentBGMNotePosを1増やす
            BGM_PlayNotePos++;

            // BGMの再生位置は終端か？
            if (BGM_PlayNotePos >= BGMEndPos) {
                // BGMの再生位置を最初へ戻す
                BGM_PlayNotePos = 0;
            }

            // BGMが再生中に効果音が再生していたら、
            // if (SE_GetIsPlay() == OFF) {
            l_NoteLength =
                *(SM_GetCurrentNote(BGM_SheetMusic, BGM_PlayNotePos));
            l_NoteTempo = SM_GetTempo(BGM_SheetMusic);
            // 選択された音符の長さをcurrentNoteLengthにセットする
            BGM_currentNoteLength = Change10msLength(l_NoteLength, l_NoteTempo);

            // ブザーの周波数を、現在の再生位置の音程へ変更する
            SM_ChangePich(BGM_SheetMusic, BGM_PlayNotePos);
            // }

        } else {
            // currentNoteLengthを1下げる
            BGM_currentNoteLength--;
        }

        // デバッグ用
        // BGM_currentNoteLengthをLEDで表示
        // UpdateLED(BGM_currentNoteLength);
    }
}

// 現在のブザーの音程をBGMの現在の再生位置の音程へ変更
// 効果音側で呼び出す用
void BGM_ChangeCurrentPich(void) {
    // 音符の高さに合わせて、タイマの周期を変える
    SM_ChangePich(BGM_SheetMusic, BGM_PlayNotePos);
}

/* -------------------------------------------------- */
// ゲッター

/* -------------------------------------------------- */
bool GetIsPlayBGM() {
    return IsPlayBGM;
}
