#include "../header/State.h"
#include "../header/Input.h"
#include "../header/Level.h"
#include "../header/Score.h"
#include "../header/Time.h"

uint8_t lastTimeForPlaySE = 0;

void ChangeState(uint8_t i_displayState)
{
    systemState.displayState = i_displayState;
}

void TitleProcess(void){
    switch(systemState.action){
        case ENTRY:
            //WriteToBuffer(TITLE);
            systemState.action = (uint8_t)DO;
            break;
        case DO:
            //SW5‚ª‰Ÿ‚³‚ê‚½‚©
            if(SWState == 0x10)
            ChangeState((uint8_t)SELECT_LEVEL);
            systemState.action = (uint8_t)ENTRY;
            break;
        default:
            break;
    }
}

void SelectLevelProcess(void){
    switch(systemState.action){
        case ENTRY:
            //WriteToBuffer(SELECTLEVEL);
            systemState.action = (uint8_t)DO;
            break;
        case DO:
            switch(SWState){
                //SW1
                case 0x01:
                    SetLevel((uint8_t)EASY);
                    //BufferToLCD(EASY);
                    break;
                //SW2
                case 0x02:
                    SetLevel((uint8_t)NORMAL);
                    //BufferToLCD(NORMAL);
                    break;
                //SW3
                case 0x04:
                    SetLevel((uint8_t)HARD);
                    //BufferToLCD(HARD);
                    break;
                //SW4
                case 0x08:
                    ChangeState((uint8_t)HS_CLEAR);
                    systemState.action = (uint8_t)ENTRY;
                    break;
                //SW5
                case 0x10:
                    ChangeState((uint8_t)START_COUNT_DOWN);
                    systemState.action = (uint8_t)ENTRY;                    
                    break;
            }
            break;
        default:
            break;
    }
}

void HSClearProcess(void){
    switch(systemState.action){
        case ENTRY:
            //BufferToLCD(HS_CLEAR);
            systemState.action = (uint8_t)DO;
            break;
        case DO:
            switch(SWState){
                case 0x01:
                    ClearHighScore(Level);
                    ChangeState((uint8_t)SELECT_LEVEL);
                    systemState.action = (uint8_t)ENTRY;                    
                    break;
                case 0x08:
                    ChangeState((uint8_t)SELECT_LEVEL);
                    systemState.action = (uint8_t)ENTRY;                    
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
    switch(systemState.action){
        case ENTRY:
            Time = 3;
            //PlaySE(countdown3sec);
            systemState.action = (uint8_t)DO;
            break;
        case DO:
            if(Time){
                if(Time < lastTimeForPlaySE){
                    //PlaySE(1&2secSE)
                    //WriteBuffer(start countdown);
                }
            }
            else{
                ChangeState((uint8_t)PLAYING_GAME);
                systemState.action = (uint8_t)ENTRY;
            }
            break;
        default:
            break;
    }
}

void PlayingGameProcess(void){
    switch(systemState.action){
        case ENTRY:
            Time = 60;
            //WriteTobuffer(playing game);
            //PlayBGM();
            systemState.action = (uint8_t)DO;
            break;
        case DO:
            if(Time){
                //MoleManager();
            }
            else{
                ChangeState((uint8_t)RESULT);
                systemState.action = (uint8_t)ENTRY;
            }
            //UpdateLED();
            break;
        default:
            break;
    }
}

void ResultProcess(void){
    switch(systemState.action){
        case ENTRY:
            //WriteToBuffer(result);
            systemState.action = (uint8_t)DO;
            break;
        case DO:
            if(SWState == 0x10){
                if(Score>HighScore[Level-1]){
                    SaveHighScore(Level);
                }
                else{
                    //‰½‚à‚µ‚È‚¢
                }
                ChangeState((uint8_t)TITLE);
                systemState.action = (uint8_t)ENTRY;           
            }
            else{
                    //‰½‚à‚µ‚È‚¢
            }
            break;
        default:
            break;
    }
}

