#include "State.h"

#include "Input.h"
#include "LCD.h"
#include "Level.h"
#include "Mole.h"
#include "Score.h"
#include "Timer.h"

uint8_t lastTimeForPlaySE = 0;

static uint8_t *str_TitleState          = {"TITLE"};
static uint8_t *str_SelectLevelState    = {"LEVEL"};
static uint8_t *str_HSClearState        = {"HSCLEAR"};
static uint8_t *str_StartCOuntDownState = {"CNT_DOWN"};
uint8_t str_PlayingGameState[16]        = {"S000 T00 _ _ _ _"};
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
                    //BufferToLCD(EASY);
                    break;
                //SW2
                case SW2:
                    //難易度設�?(NORMAL)
                    SetLevel((uint8_t)NORMAL);
                    //BufferToLCD(NORMAL);
                    break;
                //SW3
                case SW3:
                    //難易度設�?(HARD)
                    SetLevel((uint8_t)HARD);
                    //BufferToLCD(HARD);
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
    switch (SystemState.action) {
        case ENTRY:
            //残り時間設�?
            WriteToBuffer(str_StartCOuntDownState, 8);
            Time = 3;
            //PlaySE(countdown3sec);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            if (Time) {
                //残り時間が変わった時SEを鳴らす
                if (Time < lastTimeForPlaySE) {
                    //PlaySE(1&2secSE)
                    //WriteBuffer(start countdown);
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
    switch (SystemState.action) {
        case ENTRY:
            //残り時間�?60に設�?
            Time = 60;
            WriteToBuffer(str_PlayingGameState, 16);

            //BGMを鳴らす
            //PlayBGM();
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //ゲー�?中
            if (Time) {
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
                if (Score > HighScore[Level - 1]) {
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
