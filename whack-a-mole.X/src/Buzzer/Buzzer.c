/*
Buzzer

BGMとSEを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ



 */

#include "Buzzer.h"

#include "Player.h"
#include "tmr2.h"
// PWMのデューティ比を変更するため
#include "SheetMusic.h"
#include "memory.h"
#include "pwm3.h"
/* -------------------------------------------------- */
// パブリック変数
/* -------------------------------------------------- */

/* -------------------------------------------------- */
// プライベート変数
/* -------------------------------------------------- */
// BGM楽譜が入るインスタンス
// static Player_t BGM;
// SE楽譜が入るインスタンス
static Player_t SE;

// 音程テープル
uint8_t PichTable[SCALE_NUM];

static bool Update10msBuzzerFlg = OFF;

static bool IsPlayingBuzzer = OFF;

// ブザーの初期化

void Buzzer_Initialize(void) {
    uint8_t c;
    Player_Initialize(&SE);

    for (c = 0; c < SCALE_NUM; c++) {
        PichTable[c] = DATAEE_ReadByte(c + EEPROM_ADDR_SHEETMUSIC_REST);
    }
}

// ブザーの更新

void UpdateBuzzer(void) {
    // BGMStateの切り替え
    // BGM_updatePlayerState();

    // SEStateの切り替え
    // updatePlayerState(&SE);

    // どっちも再生中でなければ、PWMをストップさせる
    // if ((GetIsPlayBGM() || GetIsPlaySE()) == OFF) {
    //     IsPlayingBuzzer = OFF;
    //     TMR2_StopTimer();
    // }
    if (GetIsPlaySE() == OFF) {
        IsPlayingBuzzer = OFF;
        TMR2_StopTimer();
    }

    // 10msフラグ
    if (Update10msBuzzerFlg == ON) {
        // BGMManagerを更新
        // BGM_updatePlayerManager();
        // SEManagerを更新
        // SE_updatePlayerManager();
        // 10msフラグを下げる
        Update10msBuzzerFlg = OFF;
    }
}

// PWMを開始する
// BGM, SEで呼ばれる

void PlayBuzzer(void) {
    if (IsPlayingBuzzer == OFF) {
        TMR2_StartTimer();
        IsPlayingBuzzer = ON;
    }
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

void SM_ChangePich(SheetMusic_t *i_SheetMusic, uint16_t i_pos) {
    uint8_t l_pich = 0;

    // 音符の高さに合わせて、タイマの周期を変える
    // 音の高さを取得する
    l_pich = SM_GetCurrentNotePich(i_SheetMusic, i_pos);
    // 音の高さに合わせて、タイマの周期とデューティー比を変更
    ChangePich(l_pich);
}

// 音符の長さを10msに変換
// 入力は16分音符の個数とテンポ
// 出力はmsか

uint16_t Change10msLength(uint8_t i_NoteLength, uint16_t i_Tempo) {
    // LengthNote16th_ms = 15 * 1000 / テンポ = 16分音符の長さ(ms)
    return ((1500 / i_Tempo) * i_NoteLength);
}

void SetUpdate10msBuzzerFlg(void) {
    Update10msBuzzerFlg = ON;
}
// BGM再生開始フラグのON
void PlaySE(void) {
    SE.StartFlg = ON;
}

// SEの更新
uint8_t l_str[8];

void SE_updatePlayerManager(void) {
    uint8_t l_NoteTempo  = 0;
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
    }
}
bool GetIsPlaySE(void) {
    return SE.IsPlay;
}
