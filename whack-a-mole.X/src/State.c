#include "State.h"

#include "Buzzer/Buzzer.h"
#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Mole.h"
#include "Rand.h"
#include "Score.h"
#include "Timer.h"
// count1secを初期化するため
#include "tmr1.h"

// SW処理終了フラグ
bool l_swProcessEndFlag = 0;
//例外入力パターン(同時押し)検出フラグ
bool l_swDefaultPatternFlag = 0;

//システム構造体変数
SystemStateType SystemState;

//タイトル文字列(モグラタタキ)
static const uint8_t str_TitleState[7] = {

    0b11010011, 0b10111000, 0b11011110, 0b11010111, 0b11000000, 0b11000000, 0b10110111

};
static const uint8_t *str_HSClearState        = {"CLR HS? "};
static const uint8_t *str_HSClearState_Second = {"YES1 NO4"};
static const uint8_t *str_StartCountDownState = {"CNT_DOWN"};
static const uint8_t *str_PlayingGameState    = {"S000 T00"};
static const uint8_t *str_Score               = {"SCORE"};
static const uint8_t *str_HighScore           = {"HS"};

void ChangeState(uint8_t i_displayState) {
    if (i_displayState < 6) {
        //画面状態変更
        SystemState.displayState = i_displayState;
    }
}

void TitleProcess(void) {
    if (SystemState.action == ACTION_ENTRY) {
        //タイトル文字列書き込み
        ClrLCDBuffer();
        WriteToBufferFirst(str_TitleState, 7);
        WriteToBufferMole(1, MOLE_STATE_HOLE);
        WriteToBufferMole(2, MOLE_STATE_POP);
        WriteToBufferMole(3, MOLE_STATE_HIT);
        WriteToBufferMole(4, MOLE_STATE_HOLE);
        SystemState.action = (uint8_t)ACTION_DO;
    } else if (SystemState.action == ACTION_DO) {
        //SW5が押されたか
        if (SWState == SW5) {
            //難易度選択画面に遷移
            ChangeState((uint8_t)SELECT_LEVEL);
            SystemState.action = (uint8_t)ACTION_ENTRY;
            l_swProcessEndFlag = 1;
        } else {
            //例外入力を検出
            if (SWState) {
                l_swDefaultPatternFlag = 1;
            }
        }
        //SWStateのクリア
        if (l_swDefaultPatternFlag || l_swProcessEndFlag) {
            SWState                = 0;
            l_swProcessEndFlag     = 0;
            l_swDefaultPatternFlag = 0;
        }
    } else {
        //何もしない
    }
}

void SelectLevelProcess(void) {
    uint16_t l_HighScoreEasy   = GetHighScore(EASY);
    uint16_t l_HighScoreNormal = GetHighScore(NORMAL);
    uint16_t l_HighScoreHard   = GetHighScore(HARD);

    if (SystemState.action == ACTION_ENTRY) {
        ClrLCDBuffer();

        //難易度設定(EASY)
        SetLevel((uint8_t)EASY);
        // 1行目に"EASY"を書く
        WriteToBufferFirst(STR_LEVEL_EASY, STR_LEVEL_EASY_LEN);

        // 2行目にハイスコアを書く
        WriteToBuffer(10, str_HighScore, 2);
        WriteToBufferInt(13, l_HighScoreEasy, 3);

        SystemState.action = (uint8_t)ACTION_DO;
    } else if (SystemState.action == ACTION_DO) {
        switch (SWState) {
                //SW1
            case SW1:
                //難易度設定(EASY)
                SetLevel((uint8_t)EASY);
                // 1行目に"EASY"を書く
                WriteToBufferFirst(STR_LEVEL_EASY, STR_LEVEL_EASY_LEN);

                // 2行目にハイスコアを書く
                l_swProcessEndFlag = 1;
                WriteToBuffer(10, str_HighScore, 2);
                WriteToBufferInt(13, l_HighScoreEasy, 3);

                break;
                //SW2
            case SW2:
                //難易度設定(NORMAL)
                SetLevel((uint8_t)NORMAL);
                // 1行目に"NORMAL"を書く
                WriteToBufferFirst(STR_LEVEL_NORMAL, STR_LEVEL_NORMAL_LEN);
                // 2行目にハイスコアを書く
                l_swProcessEndFlag = 1;
                WriteToBuffer(10, str_HighScore, 2);
                WriteToBufferInt(13, l_HighScoreNormal, 3);
                break;
                //SW3
            case SW3:
                //難易度設定(HARD)
                SetLevel((uint8_t)HARD);
                // 1行目に"HARD"を書く
                WriteToBufferFirst(STR_LEVEL_HARD, STR_LEVEL_HARD_LEN);

                // 2行目にハイスコアを書く
                l_swProcessEndFlag = 1;
                WriteToBuffer(10, str_HighScore, 2);
                WriteToBufferInt(13, l_HighScoreHard, 3);
                break;
                //SW4
            case SW4:
                //ハイスコアクリア確認画面に遷移
                ChangeState((uint8_t)HS_CLEAR);
                SystemState.action = (uint8_t)ACTION_ENTRY;
                l_swProcessEndFlag = 1;
                break;
                //SW5
            case SW5:
                //ゲーム開始カウントダウン画面に遷移
                ChangeState((uint8_t)START_COUNT_DOWN);
                SystemState.action = (uint8_t)ACTION_ENTRY;
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
    } else {
        //何もしない
    }
}

void HSClearProcess(void) {
    if (SystemState.action == ACTION_ENTRY) {
        ClrLCDBuffer();
        WriteToBufferFirst(str_HSClearState, 8);
        WriteToBufferSecond(str_HSClearState_Second, 8);
        SystemState.action = (uint8_t)ACTION_DO;
    } else if (SystemState.action == ACTION_DO) {
        switch (SWState) {
            case SW1:
                //ハイスコアクリア
                SaveHighScore(Level, 0);
                ChangeState((uint8_t)SELECT_LEVEL);
                SystemState.action = (uint8_t)ACTION_ENTRY;
                l_swProcessEndFlag = 1;
                break;
            case SW4:
                ChangeState((uint8_t)SELECT_LEVEL);
                SystemState.action = (uint8_t)ACTION_ENTRY;
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
    } else {
        //何もしない
    }
}

void StartCountDownProcess(void) {
    uint8_t l_Time = 0;

    if (SystemState.action == ACTION_ENTRY) {
        //残り時間設定
        RemaingTime = 3;
        l_Time      = RemaingTime;

        ClrLCDBuffer();

        WriteToBufferFirst(str_StartCountDownState, 8);

        PlaySE();
        WriteToBufferInt(10, RemaingTime, 1);

        ClrCount1sec();
        SystemState.action = (uint8_t)ACTION_DO;
        l_swProcessEndFlag = 1;
    } else if (SystemState.action == ACTION_DO) {
        if (RemaingTime > 0) {
            //残り時間が変わった時SEを鳴らす
            if (l_Time > RemaingTime) {
                PlaySE();
                WriteToBufferInt(10, RemaingTime, 1);
                l_Time = RemaingTime;
            }
            WriteToBufferInt(10, RemaingTime, 1);
        } else {
            SWState = 0;
            ChangeState((uint8_t)PLAYING_GAME);
            SystemState.action = (uint8_t)ACTION_ENTRY;
        }
    } else {
        //何もしない
    }
}

void PlayingGameProcess(void) {
    uint8_t l_Time = 0;

    if (SystemState.action == ACTION_ENTRY) {
        //モグラ出現時間の最小最大を決定
        MinMolePopTime = 100 >> (Level);     //25-100
        MaxMolePopTime = 50 << (3 - Level);  //200-100
        ClrLCDBuffer();

        //残り時間を60に設定
        RemaingTime = 60;
        l_Time      = RemaingTime;

        // Rand関数のシード値に経過時間を加える
        AddRandSeed(TimeForRand);

        // ゲーム中の「S」や「T」を表示させる
        WriteToBufferFirst(str_PlayingGameState, 8);
        WriteToBufferMole(1, MOLE_STATE_HOLE);
        WriteToBufferMole(2, MOLE_STATE_HOLE);
        WriteToBufferMole(3, MOLE_STATE_HOLE);
        WriteToBufferMole(4, MOLE_STATE_HOLE);
        WriteToBufferInt(1, Score, 3);
        WriteToBufferInt(6, RemaingTime, 2);

        SystemState.action = (uint8_t)ACTION_DO;
    } else if (SystemState.action == ACTION_DO) {
        //ゲーム中
        if (RemaingTime > 0) {
            // タイマに変更があったら
            if (l_Time != RemaingTime) {
                WriteToBufferInt(6, RemaingTime, 2);
                l_Time = RemaingTime;
            }
            //モグラの処理
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
            SystemState.action = (uint8_t)ACTION_ENTRY;
        }
        //UpdateLED();
    } else {
        //何もしない
    }
}

void ResultProcess(void) {
    uint16_t l_HighScore = GetHighScore(Level);

    if (SystemState.action == ACTION_ENTRY) {
        // 画面クリア
        ClrLCDBuffer();
        // 上段一番左から"SCORE"を表示
        WriteToBufferFirst(str_Score, 5);
        // SCOREを書き込む
        WriteToBufferInt(5, Score, 3);

        WriteToBuffer(10, str_HighScore, 2);
        // HIGHSCOREを書き込む
        WriteToBufferInt(13, l_HighScore, 3);

        // Randのシード値をEEPROMに書き込む
        SaveRandSeed();

        SystemState.action = (uint8_t)ACTION_DO;
    } else if (SystemState.action == ACTION_DO) {
        //SW5が押されたか
        if (SWState == SW5) {
            //ハイスコア更新処理
            if (Score > l_HighScore) {
                SaveHighScore(Level, Score);
                l_swProcessEndFlag = 1;
            }
            Score = 0;
            //タイトル画面に遷移
            ChangeState((uint8_t)TITLE);
            SystemState.action = (uint8_t)ACTION_ENTRY;
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
    } else {
        //何もしない
    }
}
