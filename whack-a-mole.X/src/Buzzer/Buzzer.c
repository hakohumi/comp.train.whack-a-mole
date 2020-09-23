/*
Buzzer

BGMとSEを管理する
管理する項目
- それぞれの再生位置
- それぞれの再生開始・停止フラグ
- それぞれの再生中フラグ



 */

#include "Buzzer.h"

#include "tmr2.h"
// PWMのデューティ比を変更するため
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

static bool Update10msBuzzerFlg = OFF;

static bool IsPlayingBuzzer = OFF;

#define TEMPO 230
#define MUSIC_LEN 1
#define PICH DO2

// 音符の長さを10msに変換
// 入力は16分音符の個数とテンポ
// 出力はmsか

#define Change10msLength(N) (1500 / N)

// ブザーの初期化
void Buzzer_Initialize(void) {
    // 楽譜の最後の位置を記録
    SE.currentNoteLength = 0;
    SE.IsPlay            = OFF;
    SE.StartFlg          = OFF;
}

// ブザーの更新
void UpdateBuzzer(void) {
    // SEStateの切り替え
    updatePlayerState();
    // どっちも再生中でなければ、PWMをストップさせる

    if (SE.IsPlay == OFF) {
        IsPlayingBuzzer = OFF;
        TMR2_StopTimer();
    }

    // 10msフラグ
    if (Update10msBuzzerFlg == ON) {
        // SEManagerを更新
        SE_updatePlayerManager();
        // 10msフラグを下げる
        Update10msBuzzerFlg = OFF;
    }
}

/* -------------------------------------------------- */
// 頭出し処理

/* -------------------------------------------------- */

void updatePlayerState(void) {
    // 再生フラグが立ったか？
    // StartFlg
    if (SE.StartFlg == ON) {
        // StartFlgを下げる
        SE.StartFlg = OFF;

        if (SE.IsPlay == ON) {
            // SEのcurrentNotePosを最初の位置へクリア
            // returnBeginPlayPos();
        } else {
            // IsPlayをtrueに変更する
            SE.IsPlay = true;

            // 選択された音符の長さをcurrentNoteLengthにセットする
            SE.currentNoteLength = Change10msLength(TEMPO);

            // 音程の変更
            // タイマの周期とデューティー比を変更
            // 音符の高さに合わせて、タイマの周期を変える
            // 音の高さを取得する
            // 音の高さに合わせて、タイマの周期とデューティー比を変更
            // タイマに書き込み
            TMR2_LoadPeriodRegister(PICH);
            // PWMのデューティー比を50%になるように変更
            PWM3_LoadDutyValue(PICH / 2);

            // PWM開始
            if (IsPlayingBuzzer == OFF) {
                TMR2_StartTimer();
                IsPlayingBuzzer = ON;
            };
        }
    }
}

// SEの更新
void SE_updatePlayerManager(void) {
    uint8_t l_NoteTempo  = 0;
    uint8_t l_NoteLength = 0;

    // 現在SEが再生されているか
    if (SE.IsPlay == ON) {
        // 現在選択されている音符の長さ分の時間は経過したか？
        if (SE.currentNoteLength == 0) {
            // IsPlayをfalseに変更する
            SE.IsPlay = false;
        } else {
            // currentNoteLengthを1下げる
            SE.currentNoteLength--;
        }
    }
}

void SetUpdate10msBuzzerFlg(void) {
    Update10msBuzzerFlg = ON;
}
// BGM再生開始フラグのON

void PlaySE(void) {
    SE.StartFlg = ON;
}
