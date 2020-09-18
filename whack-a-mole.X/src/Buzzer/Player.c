/*
BGM

BGMを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ

 */

#include "Player.h"

#include "Buzzer.h"
#include "SheetMusic.h"
// LEDでデバッグするため
#include "LCD.h"
#include "LED.h"

/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */
// BGM楽譜が入るインスタンス
static Player_t BGM;
// SE楽譜が入るインスタンス
static Player_t SE;

/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */
/* -------------------------------------------------- */

// 初期化

void Player_Initialize(void) {
    Player_t_Init(&BGM, SM_BGM_DOREMI);
    Player_t_Init(&SE, SM_SE_DOREMI);
}

void Player_t_Init(Player_t *i_Player, uint8_t i_SM) {
    // SheetMusicのセット
    i_Player->SheetMusic = SheetMusic_Initialize(i_SM);
    i_Player->PlayNotePos = 0;
    // 楽譜の最後の位置を記録
    i_Player->EndPos = SM_GetMaxNotes(i_Player->SheetMusic);
    i_Player->currentNoteLength = 0;
    i_Player->IsPlay = OFF;
    i_Player->StartFlg = OFF;
    i_Player->StopFlg = OFF;
}

// BGM再生開始フラグのON

void PlayBGM(void) { BGM.StartFlg = ON; }

// BGM再生開始フラグのON
void PlaySE(void) { SE.StartFlg = ON; }

/* -------------------------------------------------- */
// 頭出し処理

/* -------------------------------------------------- */

void returnBeginPlayPos(Player_t *i_Player) {
    uint8_t l_NoteTempo = SM_GetTempo(i_Player->SheetMusic);
    uint8_t l_NoteLength = *(SM_GetCurrentNote(i_Player->SheetMusic, 0));

    // 選択された音符の長さをcurrentNoteLengthにセットする
    i_Player->currentNoteLength = Change10msLength(l_NoteLength, l_NoteTempo);

    // 音符の高さに合わせて、タイマの周期を変える
    SM_ChangePich(i_Player->SheetMusic, 0);
}

void updatePlayerState(Player_t *i_Player) {
    // 再生フラグが立ったか？
    // StartFlg
    if (i_Player->StartFlg == ON) {
        // StartFlgを下げる
        i_Player->StartFlg = OFF;

        // もしSEが選択されていたら
        // 現在こうか再生されているか
        if ((i_Player == &SE) && i_Player->IsPlay == ON) {
            // SEのcurrentNotePosを最初の位置へクリア
            returnBeginPlayPos(i_Player);
        } else {
            // IsPlayをtrueに変更する
            i_Player->IsPlay = true;

            // 最初の処理
            returnBeginPlayPos(i_Player);

            // PWM開始
            PlayBuzzer();
        }
    }

    // 停止フラグが立ったか?
    // StopFlg
    if (i_Player->StopFlg == ON) {
        // BGMStopFlgを下げる
        i_Player->StopFlg = OFF;

        // IsPlayをfalseに変更する
        i_Player->IsPlay = false;

        if (i_Player == &SE) {
            // ブザーの音程をBGMの現在の再生位置の音程へ設定する
            BGM_ChangeCurrentPich();
        }
    }
}

void BGM_updatePlayerState(void) { updatePlayerState(&BGM); }

void SE_updatePlayerState(void) { updatePlayerState(&SE); }

// void BGM_updatePlayerState(void) {
//     // 再生フラグが立ったか？
//     // StartFlg
//     if (BGM.StartFlg == ON) {
//         // StartFlgを下げる
//         BGM.StartFlg = OFF;

//         // IsPlayをtrueに変更する
//         BGM.IsPlay = true;

//         // 最初の処理
//         returnBeginPlayPos(&BGM);

//         // PWM開始
//         PlayBuzzer();
//     }

//     // 停止フラグが立ったか?
//     // StopFlg
//     if (BGM.StopFlg == ON) {
//         // BGMStopFlgを下げる
//         BGM.StopFlg = OFF;

//         // IsPlayをfalseに変更する
//         BGM.IsPlay = false;
//     }
// }

// // SEStateの切り替え
// void SE_updatePlayerState(void) {
//     // SE再生フラグが立ったか？
//     // SEStartFlg
//     if (SE.StartFlg == ON) {
//         // SEStartFlgを下げる
//         SE.StartFlg = OFF;

//         // 現在再生されているか
//         if (SE.IsPlay == ON) {
//             // SEのcurrentNotePosを最初の位置へクリア
//             returnBeginPlayPos(&SE);
//         } else {
//             // IsPlaySEをtrueに変更する
//             SE.IsPlay = true;

//             // 最初の処理
//             returnBeginPlayPos(&SE);

//             // PWM開始
//             PlayBuzzer();
//         }
//     }

//     // SE停止フラグが立ったか?
//     // SEStopFlg
//     if (SE.StopFlg == ON) {
//         // SEStopFlgを下げる
//         SE.StopFlg = OFF;

//         // IsPlaySEをfalseに変更する
//         SE.IsPlay = false;

//         // ブザーの音程をBGMの現在の再生位置の音程へ設定する
//         BGM_ChangeCurrentPich();
//     }
// }

// BGM_Playerの更新
void BGM_updatePlayerManager(void) {
    uint8_t l_NoteTempo = 0;
    uint8_t l_NoteLength = 0;

    // 現在BGMが再生されているか
    if (BGM.IsPlay == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (BGM.currentNoteLength == 0) {
            // currentNotePosを1増やす
            BGM.PlayNotePos++;

            // Playerの再生位置は終端か？
            if (BGM.PlayNotePos >= BGM.EndPos) {
                // Playerの再生位置を最初へ戻す
                BGM.PlayNotePos = 0;
            }

            // Playerが再生中に効果音が再生していたら、
            // if (GetIsPlaySE() == OFF) {
            l_NoteLength =
                *(SM_GetCurrentNote(BGM.SheetMusic, BGM.PlayNotePos));
            l_NoteTempo = SM_GetTempo(BGM.SheetMusic);
            // 選択された音符の長さをcurrentNoteLengthにセットする
            BGM.currentNoteLength = Change10msLength(l_NoteLength, l_NoteTempo);

            // ブザーの周波数を、現在の再生位置の音程へ変更する
            SM_ChangePich(BGM.SheetMusic, BGM.PlayNotePos);
            // }

        } else {
            // currentNoteLengthを1下げる
            BGM.currentNoteLength--;
        }

        // デバッグ用
        // BGM_currentNoteLengthをLEDで表示
        // UpdateLED(BGM_currentNoteLength);
    }
}

// SEの更新
uint8_t l_str[8];

void SE_updatePlayerManager(void) {
    uint8_t l_NoteTempo = 0;
    uint8_t l_NoteLength = 0;

    // 現在SEが再生されているか
    if (SE.IsPlay == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (SE.currentNoteLength == 0) {
            // currentBGMNotePosを1増やす
            SE.PlayNotePos++;

            // SEの再生位置は終端か？
            if (SE.PlayNotePos >= SE.EndPos) {
                // BGMの再生位置を最初へ戻す
                SE.PlayNotePos = 0;

                // SEの再生状態をOFFにする
                SE.StopFlg = ON;
            } else {
                l_NoteLength =
                    *(SM_GetCurrentNote(SE.SheetMusic, SE.PlayNotePos));
                l_NoteTempo = SM_GetTempo(SE.SheetMusic);
                // 選択された音符の長さをcurrentNoteLengthにセットする
                SE.currentNoteLength =
                    Change10msLength(l_NoteLength, l_NoteTempo);

                // ブザーの周波数を、現在の再生位置の音程へ変更する
                SM_ChangePich(SE.SheetMusic, SE.PlayNotePos);
            }
        } else {
            // currentNoteLengthを1下げる
            SE.currentNoteLength--;
        }
        // デバッグ用
        // currentNoteLengthをLEDで表示
        UpdateLED(*(SM_GetCurrentNote(SE.SheetMusic, SE.PlayNotePos)));

        ItoStr(SE.currentNoteLength, l_str, 8);
        WriteToBufferFirst(l_str, 8);
    }
}

// 現在のブザーの音程をBGMの現在の再生位置の音程へ変更
// 効果音側で呼び出す用
void BGM_ChangeCurrentPich(void) {
    // 音符の高さに合わせて、タイマの周期を変える
    SM_ChangePich(BGM.SheetMusic, BGM.PlayNotePos);
}

/* -------------------------------------------------- */
// ゲッター

/* -------------------------------------------------- */
bool GetIsPlayBGM() { return BGM.IsPlay; }
bool GetIsPlaySE() { return SE.IsPlay; }
