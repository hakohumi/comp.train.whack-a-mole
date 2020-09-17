#include "State.h"

#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Mole.h"
#include "Score.h"
#include "Timer.h"

#include <string.h>
uint8_t lastTimeForPlaySE = 0;

static uint8_t *str_TitleState          = {"TITLE"};
static uint8_t *str_SelectLevelState    = {"LEVEL"};
static uint8_t *str_HSClearState        = {"HSCLEAR"};
static uint8_t *str_StartCOuntDownState = {"CNT_DOWN"};
uint8_t str_PlayingGameState[16]        = {"S000 T00        "};
static uint8_t *str_ResultState         = {"RESULT"};

void ChangeState(uint8_t i_displayState) {
    if (i_displayState < 6) {
        //画面状態変更
        SystemState.displayState = i_displayState;
    }
}

void TitleProcess(void) {
    switch (SystemState.action) {
        case ENTRY:
            //タイトル文字列書き込み
            WriteToBuffer(str_TitleState, 5);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if (SWState == SW5) {
                //難易度選択画面に遷移
                ChangeState((uint8_t)SELECT_LEVEL);
                SystemState.action = (uint8_t)ENTRY;
            }
            SWState = 0x00;
            break;
        default:
            break;
    }
}

void SelectLevelProcess(void) {
    uint16_t l_HighScore = 0;
    uint8_t l_str_line[8];
    memset(l_str_line, '\0', 8);
    switch (SystemState.action) {
        case ENTRY:
            WriteToBuffer(str_SelectLevelState, 5);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch (SWState) {
                //SW1
                case SW1:
                    //難易度設�?(EASY)
                    SetLevel((uint8_t)EASY);
                    // 1行目に"EASY"を書く
                    WriteToBufferFirst(STR_LEVEL_EASY, STR_LEVEL_EASY_LEN);
                    // ハイスコアをEEPROMから取り出す
                    l_HighScore = GetHighScore(EASY);
                    // 取り出したハイスコアを文字列へ変換
                    ItoStr(l_HighScore, l_str_line, 3);
                    // 2行目にハイスコアを書く
                    WriteToBufferSecond(l_str_line, 3);

                    break;
                    //SW2
                case SW2:
                    //難易度設�?(NORMAL)
                    SetLevel((uint8_t)NORMAL);
                    // 1行目に"NORMAL"を書く
                    WriteToBufferFirst(STR_LEVEL_NORMAL, STR_LEVEL_NORMAL_LEN);
                    // ハイスコアをEEPROMから取り出す
                    l_HighScore = GetHighScore(NORMAL);
                    // 取り出したハイスコアを文字列へ変換
                    ItoStr(l_HighScore, l_str_line, 3);
                    // 2行目にハイスコアを書く
                    WriteToBufferSecond(l_str_line, 3);
                    break;
                    //SW3
                case SW3:
                    //難易度設�?(HARD)
                    SetLevel((uint8_t)HARD);
                    // 1行目に"HARD"を書く
                    WriteToBufferFirst(STR_LEVEL_HARD, STR_LEVEL_HARD_LEN);
                    // ハイスコアをEEPROMから取り出す
                    l_HighScore = GetHighScore(HARD);
                    // 取り出したハイスコアを文字列へ変換
                    ItoStr(l_HighScore, l_str_line, 3);
                    // 2行目にハイスコアを書く
                    WriteToBufferSecond(l_str_line, 3);
                    break;
                    //SW4
                case SW4:
                    //ハイスコアクリア確認画面に遷移
                    ChangeState((uint8_t)HS_CLEAR);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
                    //SW5
                case SW5:
                    //ゲー�?開始カウントダウン画面に遷移
                    ChangeState((uint8_t)START_COUNT_DOWN);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
            }
            SWState = 0x00;
            break;
        default:
            break;
    }
}

void HSClearProcess(void) {
    switch (SystemState.action) {
        case ENTRY:
            WriteToBuffer(str_HSClearState, 7);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch (SWState) {
                case SW1:
                    //ハイスコアクリア
                    ClearHighScore(Level);
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
                case SW4:
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
                default:
                    break;
            }
            SWState = 0x00;
            break;
        default:
            break;
    }
}

void StartCountDownProcess(void) {
    uint8_t l_Time = 0;

    switch (SystemState.action) {
        case ENTRY:
            //残り時間設�?
            WriteToBuffer(str_StartCOuntDownState, 8);

            Time   = 3;
            l_Time = Time;
            //PlaySE(countdown3sec);
            SystemState.action = (uint8_t)DO;
            WriteToBufferCountDown(Time);
            break;
        case DO:
            if (Time) {
                //残り時間が変わった時SEを鳴らす
                if (Time < l_Time) {
                    //PlaySE(1&2secSE)
                    WriteToBufferCountDown(Time);
                    l_Time = Time;
                }
            }
            //残り時間0でゲー�?中画面に遷移
            else {
                ChangeState((uint8_t)PLAYING_GAME);
                SystemState.action = (uint8_t)ENTRY;
            }
            break;
        default:
            break;
    }
}

void PlayingGameProcess(void) {
    uint8_t l_Time = 0;

    switch (SystemState.action) {
        case ENTRY:
            //残り時間�?60に設�?
            Time   = 60;
            l_Time = Time;
            WriteToBuffer(str_PlayingGameState, 16);
            WriteToBufferMole(1, HOLE);
            WriteToBufferMole(2, HOLE);
            WriteToBufferMole(3, HOLE);
            WriteToBufferMole(4, HOLE);
            WriteToBufferScore(Score);
            WriteToBufferTime(Time);

            //BGMを鳴らす
            //PlayBGM();
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //ゲー�?中
            if (Time) {
                // タイマに変更があったら
                if (l_Time != Time) {
                    WriteToBufferTime(Time);
                    l_Time = Time;
                }
                //モグラの処�?
                //MoleManager();
                MoleXProcess(&mole1);
                MoleXProcess(&mole2);
                MoleXProcess(&mole3);
                MoleXProcess(&mole4);
                SWState = 0;
            }
            //残り時間0
            else {
                //BGM停止
                //StopBGM
                //リザルト画面に遷移
                ChangeState((uint8_t)RESULT);
                SystemState.action = (uint8_t)ENTRY;
            }
            //UpdateLED();
            break;
        default:
            break;
    }
}

void ResultProcess(void) {
    switch (SystemState.action) {
        case ENTRY:
            WriteToBuffer(str_ResultState, 6);

            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if (SWState == SW5) {
                //ハイスコア更新処�?
                if (Score > GetHighScore(Level)) {
                    SaveHighScore(Level);
                } else {
                    //何もしな�?
                }
                //タイトル画面に遷移
                ChangeState((uint8_t)TITLE);
                SystemState.action = (uint8_t)ENTRY;
            } else {
                //何もしな�?
            }
            SWState = 0x00;
            break;
        default:
            break;
    }
}
