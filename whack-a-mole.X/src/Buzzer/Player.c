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

/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */


/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート関数
/* -------------------------------------------------- */
/* -------------------------------------------------- */

// 初期化

void Player_Initialize(Player_t *i_Player) {
    // Player_t_Init(&BGM, SM_BGM_DOREMI);
    Player_t_Init(i_Player, SM_SE_DOREMI);
}

void Player_t_Init(Player_t *i_Player, uint8_t i_SM) {
    // SheetMusicのセット
    i_Player->SheetMusic  = SheetMusic_Initialize(i_SM);
    i_Player->PlayNotePos = 0;
    // 楽譜の最後の位置を記録
    i_Player->EndPos            = SM_GetMaxNotes(i_Player->SheetMusic);
    i_Player->currentNoteLength = 0;
    i_Player->IsPlay            = OFF;
    i_Player->StartFlg          = OFF;
}

/* -------------------------------------------------- */
// 頭出し処理

/* -------------------------------------------------- */

void returnBeginPlayPos(Player_t *i_Player) {
    uint8_t l_NoteTempo  = SM_GetTempo(i_Player->SheetMusic);
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
        // if ((i_Player == &SE) && i_Player->IsPlay == ON) {
        if (i_Player->IsPlay == ON) {
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
}