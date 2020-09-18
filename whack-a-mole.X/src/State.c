#include "State.h"

#include <string.h>

#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Mole.h"
#include "Rand.h"
#include "Score.h"
#include "Timer.h"

uint8_t l_swProcessEndFlag     = 0;
uint8_t l_swDefaultPatternFlag = 0;

// count1secを初期化するため
#include "tmr1.h"

//システム構造体変数
SystemStateType SystemState;

static uint8_t str_TitleState[7] = {
    0b11010011,
    0b10111000,
    0b11011110,
    0b11010111,
    0b11000000,
    0b11000000,
    0b10110111

};
static uint8_t *str_HSClearState        = {"CLR HS? "};
static uint8_t *str_HSClearState_Second = {"YES1 NO4"};
static uint8_t *str_StartCountDownState = {"CNT_DOWN"};
static uint8_t *str_PlayingGameState    = {"S000 T00"};
static uint8_t *str_Score               = {"SCORE"};
static uint8_t *str_HighScore           = {"HS"};

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
            ClrLCDBuffer();
            WriteToBufferFirst(str_TitleState, 7);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if (SWState == SW5) {
                //難易度選択画面に遷移
                ChangeState((uint8_t)SELECT_LEVEL);
                SystemState.action = (uint8_t)ENTRY;
                l_swProcessEndFlag = 1;
            } else {
                if (SWState) {
                    l_swDefaultPatternFlag = 1;
                }
            }
            if (l_swDefaultPatternFlag || l_swProcessEndFlag) {
                SWState                = 0;
                l_swProcessEndFlag     = 0;
                l_swDefaultPatternFlag = 0;
            }
            break;
        default:
            break;
    }
}

void SelectLevelProcess(void) {
    uint16_t l_HighScore = 0;
    switch (SystemState.action) {
        case ENTRY:
            ClrLCDBuffer();

            //難易度設�?(EASY)
            SetLevel((uint8_t)EASY);
            // 1行目に"EASY"を書く
            WriteToBufferFirst(STR_LEVEL_EASY, STR_LEVEL_EASY_LEN);
            // ハイスコアをEEPROMから取り出す
            l_HighScore = GetHighScore(EASY);
            // 2行目にハイスコアを書く
            WriteToBuffer(10, str_HighScore, 2);
            WriteToBufferInt(13, l_HighScore, 3);

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
                    // 2行目にハイスコアを書く
                    l_swProcessEndFlag = 1;
                    WriteToBuffer(10, str_HighScore, 2);
                    WriteToBufferInt(13, l_HighScore, 3);

                    break;
                    //SW2
                case SW2:
                    //難易度設�?(NORMAL)
                    SetLevel((uint8_t)NORMAL);
                    // 1行目に"NORMAL"を書く
                    WriteToBufferFirst(STR_LEVEL_NORMAL, STR_LEVEL_NORMAL_LEN);
                    // ハイスコアをEEPROMから取り出す
                    l_HighScore = GetHighScore(NORMAL);
                    // 2行目にハイスコアを書く
                    l_swProcessEndFlag = 1;
                    WriteToBuffer(10, str_HighScore, 2);
                    WriteToBufferInt(13, l_HighScore, 3);
                    break;
                    //SW3
                case SW3:
                    //難易度設�?(HARD)
                    SetLevel((uint8_t)HARD);
                    // 1行目に"HARD"を書く
                    WriteToBufferFirst(STR_LEVEL_HARD, STR_LEVEL_HARD_LEN);
                    // ハイスコアをEEPROMから取り出す
                    l_HighScore = GetHighScore(HARD);

                    // 2行目にハイスコアを書く
                    l_swProcessEndFlag = 1;
                    WriteToBuffer(10, str_HighScore, 2);
                    WriteToBufferInt(13, l_HighScore, 3);
                    break;
                    //SW4
                case SW4:
                    //ハイスコアクリア確認画面に遷移
                    ChangeState((uint8_t)HS_CLEAR);
                    SystemState.action = (uint8_t)ENTRY;
                    l_swProcessEndFlag = 1;
                    break;
                    //SW5
                case SW5:
                    //ゲー�?開始カウントダウン画面に遷移
                    ChangeState((uint8_t)START_COUNT_DOWN);
                    SystemState.action = (uint8_t)ENTRY;
                    l_swProcessEndFlag = 1;
                    break;
                default:
                    if (SWState) {
                        l_swDefaultPatternFlag = 1;
                    }
            }
            if (l_swDefaultPatternFlag || l_swProcessEndFlag) {
                SWState                = 0;
                l_swProcessEndFlag     = 0;
                l_swDefaultPatternFlag = 0;
            }
            break;
        default:
            break;
    }
}

void HSClearProcess(void) {
    switch (SystemState.action) {
        case ENTRY:
            ClrLCDBuffer();
            WriteToBufferFirst(str_HSClearState, 8);
            WriteToBufferSecond(str_HSClearState_Second, 8);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch (SWState) {
                case SW1:
                    //ハイスコアクリア
                    SaveHighScore(Level, 0);
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;
                    l_swProcessEndFlag = 1;
                    break;
                case SW4:
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;
                    l_swProcessEndFlag = 1;
                    break;
                default:
                    if (SWState) {
                        l_swDefaultPatternFlag = 1;
                    }
                    break;
            }
            if (l_swDefaultPatternFlag || l_swProcessEndFlag) {
                SWState                = 0;
                l_swProcessEndFlag     = 0;
                l_swDefaultPatternFlag = 0;
            }
            break;
        default:
            break;
    }
}

void StartCountDownProcess(void) {
    uint8_t l_Time = 0;

    switch (SystemState.action) {
        case ENTRY:
            Time   = 3;
            l_Time = Time;

            ClrLCDBuffer();
            //残り時間設�?
            WriteToBufferFirst(str_StartCountDownState, 8);

            //PlaySE(countdown3sec);
            WriteToBufferInt(10, Time, 1);

            ClrCount1sec();
            SystemState.action = (uint8_t)DO;
            l_swProcessEndFlag = 1;
            break;
        case DO:
            if (Time) {
                //残り時間が変わった時SEを鳴らす
                if (Time < l_Time) {
                    //PlaySE(1&2secSE)
                    WriteToBufferInt(10, Time, 1);
                    l_Time = Time;
                }

                WriteToBufferInt(10, Time, 1);
            }  //残り時間0でゲー�?中画面に遷移
            else {
                SWState = 0;
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
            //モグラ出現時間の最小最大を決定
            MinMolePopTime = 100 >> (Level);     //25-100
            MaxMolePopTime = 50 << (3 - Level);  //200-100
            ClrLCDBuffer();

            //残り時間�?60に設�?
            Time   = 60;
            l_Time = Time;

            // Rand関数のシード値に経過時間を加える
            AddRandSeed(TimeForRand);

            // ゲーム中の「S」や「T」を表示させる
            WriteToBufferFirst(str_PlayingGameState, 8);
            WriteToBufferMole(1, HOLE);
            WriteToBufferMole(2, HOLE);
            WriteToBufferMole(3, HOLE);
            WriteToBufferMole(4, HOLE);
            WriteToBufferInt(1, Score, 3);
            WriteToBufferInt(6, Time, 2);

            //BGMを鳴らす
            //PlayBGM();
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //ゲー�?中
            if (Time) {
                // タイマに変更があったら
                if (l_Time != Time) {
                    WriteToBufferInt(6, Time, 2);
                    l_Time = Time;
                }
                //モグラの処�?
                //MoleManager();
                MoleXProcess(&mole1);
                MoleXProcess(&mole2);
                MoleXProcess(&mole3);
                MoleXProcess(&mole4);
                SWState &= ~SW5;
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
    uint16_t l_HighScore;
    switch (SystemState.action) {
        case ENTRY:

            // 画面クリア
            ClrLCDBuffer();
            // 上段一番左から"SCORE"を表示
            WriteToBufferFirst(str_Score, 5);
            // SCOREを書き込む
            WriteToBufferInt(5, Score, 3);

            l_HighScore = GetHighScore(Level);

            WriteToBuffer(10, str_HighScore, 2);
            // HIGHSCOREを書き込む
            WriteToBufferInt(13, l_HighScore, 3);

            // Randのシード値をEEPROMに書き込む
            SaveRandSeed();

            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if (SWState == SW5) {
                //ハイスコア更新処�?
                if (Score > GetHighScore(Level)) {
                    SaveHighScore(Level, Score);
                    l_swProcessEndFlag = 1;
                }
                Score = 0;
                //タイトル画面に遷移
                ChangeState((uint8_t)TITLE);
                SystemState.action = (uint8_t)ENTRY;
            } else {
                if (SWState) {
                    l_swDefaultPatternFlag = 1;
                }
            }
            if (l_swDefaultPatternFlag || l_swProcessEndFlag) {
                SWState                = 0;
                l_swProcessEndFlag     = 0;
                l_swDefaultPatternFlag = 0;
            }
            break;
        default:
            break;
    }
}
