#include "../header/State.h"
#include "../header/Input.h"
#include "../header/Level.h"
#include "../header/Score.h"
#include "../header/Time.h"
#include "../header/Mole.h"

uint8_t lastTimeForPlaySE = 0;

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
            //WriteToBuffer(TITLE);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if(SWState == 0x10){
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
            //WriteToBuffer(SELECTLEVEL);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch(SWState){
                //SW1
                case 0x01:
                    //難易度設定(EASY)
                    SetLevel((uint8_t)EASY);
                    //BufferToLCD(EASY);
                    break;
                //SW2
                case 0x02:
                    //難易度設定(NORMAL)
                    SetLevel((uint8_t)NORMAL);
                    //BufferToLCD(NORMAL);
                    break;
                //SW3
                case 0x04:
                    //難易度設定(HARD)
                    SetLevel((uint8_t)HARD);
                    //BufferToLCD(HARD);
                    break;
                //SW4
                case 0x08:
                    //ハイスコアクリア確認画面に遷移
                    ChangeState((uint8_t)HS_CLEAR);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
                //SW5
                case 0x10:
                    //ゲーム開始カウントダウン画面に遷移
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
            //BufferToLCD(HS_CLEAR);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            switch(SWState){
                case 0x01:
                    //ハイスコアクリア
                    ClearHighScore(Level);
                    ChangeState((uint8_t)SELECT_LEVEL);
                    SystemState.action = (uint8_t)ENTRY;                    
                    break;
                case 0x08:
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
            //残り時間設定
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
            //残り時間0でゲーム中画面に遷移
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
            //残り時間を60に設定
            Time = 60;
            //WriteTobuffer(playing game);
            //BGMを鳴らす
            //PlayBGM();
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //ゲーム中
            if(Time){
                //モグラの処理
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
            //WriteToBuffer(result);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5が押されたか
            if(SWState == 0x10){
                //ハイスコア更新処理
                if(Score>HighScore[Level-1]){
                    SaveHighScore(Level);
                }
                else{
                    //何もしない
                }
                //タイトル画面に遷移
                ChangeState((uint8_t)TITLE);
                SystemState.action = (uint8_t)ENTRY;           
            }
            else{
                    //何もしない
            }
            break;
        default:
            break;
    }
}

