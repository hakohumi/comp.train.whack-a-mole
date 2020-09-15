#include "State.h"
#include "Input.h"
#include "Level.h"
#include "Score.h"
#include "Timer.h"
#include "Mole.h"
#include "LCD.h"

uint8_t lastTimeForPlaySE = 0;

static uint8_t *str_TitleState = {"TITLE"};
static uint8_t *str_SelectLevelState = {"LEVEL"};
static uint8_t *str_HSClearState = {"HSCLEAR"};
static uint8_t *str_StartCOuntDownState = {"CNT_DOWN"};
static uint8_t *str_PlayingGameState = {"PLAYGAME"};
static uint8_t *str_ResultState = {"RESULT"};

void ChangeState(uint8_t i_displayState)
{
    if(i_displayState < 6){
        //画面状態変更
        SystemState.displayState = i_displayState;
    }
}

void TitleProcess(void){
    switch(SystemState.action){
        case ENTRY:
            WriteToBuffer(str_TitleState,5);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if(SWState == 0x08){
                SWState = 0x00;
                //難易度選択画面に遷移
                ChangeState((uint8_t)SELECT_LEVEL);
                SystemState.action = (uint8_t)ENTRY;
            }
            break;
        default:
            break;
    }
}

void SelectLevelProcess(void){
    switch(SystemState.action){
        case ENTRY:
            WriteToBuffer(str_SelectLevelState,5);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch(SWState){
                //SW1
                case 0x01:
                    SWState = 0x00;
                    //難易度設�?(EASY)
                    SetLevel((uint8_t)EASY);
                    //BufferToLCD(EASY);
                    break;
                //SW2
                case 0x02:
                    SWState = 0x00;
                    //難易度設�?(NORMAL)
                    SetLevel((uint8_t)NORMAL);
                    //BufferToLCD(NORMAL);
                    break;
                //SW3
                case 0x04:
                    SWState = 0x00;
                    //難易度設�?(HARD)
                    SetLevel((uint8_t)HARD);
                    //BufferToLCD(HARD);
                    break;
                //SW4
                case 0x08:
                    SWState = 0x00;
                    //ハイスコアクリア確認画面に遷移
                    ChangeState((uint8_t)HS_CLEAR);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
                //SW5
                case 0x10:
                    SWState = 0x00;
                    //ゲー�?開始カウントダウン画面に遷移
                    ChangeState((uint8_t)START_COUNT_DOWN);
                    SystemState.action = (uint8_t)ENTRY;                    
                    break;
            }
            break;
        default:
            break;
    }
}

void HSClearProcess(void){
    switch(SystemState.action){
        case ENTRY:
            WriteToBuffer(str_HSClearState,7);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch(SWState){
                case 0x01:
                    SWState = 0x00;
                    //ハイスコアクリア
                    ClearHighScore(Level);
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;                    
                    break;
                case 0x08:
                    SWState = 0x00;
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;                    
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void StartCountDownProcess(void){
    switch(SystemState.action){
        case ENTRY:
            //残り時間設�?
            WriteToBuffer(str_StartCOuntDownState,8);
            Time = 3;
            //PlaySE(countdown3sec);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            if(Time){
                //残り時間が変わった時SEを鳴らす
                if(Time < lastTimeForPlaySE){
                    //PlaySE(1&2secSE)
                    //WriteBuffer(start countdown);
                }
            }
            //残り時間0でゲー�?中画面に遷移
            else{
                ChangeState((uint8_t)PLAYING_GAME);
                SystemState.action = (uint8_t)ENTRY;
            }
            break;
        default:
            break;
    }
}

void PlayingGameProcess(void){
    switch(SystemState.action){
        case ENTRY:
            //残り時間�?60に設�?
            Time = 60;
            WriteToBuffer(str_PlayingGameState,8);
            //BGMを鳴らす
            //PlayBGM();
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //ゲー�?中
            if(Time){
                //モグラの処�?
                MoleManager();
            }
            //残り時間0
            else{
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

void ResultProcess(void){
    switch(SystemState.action){
        case ENTRY:
            WriteToBuffer(str_ResultState,6);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if(SWState == 0x10){
                SWState = 0x00;
                //ハイスコア更新処�?
                if(Score>HighScore[Level-1]){
                    SaveHighScore(Level);
                }
                else{
                    //何もしな�?
                }
                //タイトル画面に遷移
                ChangeState((uint8_t)TITLE);
                SystemState.action = (uint8_t)ENTRY;           
            }
            else{
                    //何もしな�?
            }
            break;
        default:
            break;
    }
}

