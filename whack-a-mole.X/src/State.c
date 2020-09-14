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
        //��ʏ�ԕύX
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
            //SW5�������ꂽ��
            if(SWState == 0x10){
                //��Փx�I����ʂɑJ��
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
                    //��Փx�ݒ�(EASY)
                    SetLevel((uint8_t)EASY);
                    //BufferToLCD(EASY);
                    break;
                //SW2
                case 0x02:
                    //��Փx�ݒ�(NORMAL)
                    SetLevel((uint8_t)NORMAL);
                    //BufferToLCD(NORMAL);
                    break;
                //SW3
                case 0x04:
                    //��Փx�ݒ�(HARD)
                    SetLevel((uint8_t)HARD);
                    //BufferToLCD(HARD);
                    break;
                //SW4
                case 0x08:
                    //�n�C�X�R�A�N���A�m�F��ʂɑJ��
                    ChangeState((uint8_t)HS_CLEAR);
                    SystemState.action = (uint8_t)ENTRY;
                    break;
                //SW5
                case 0x10:
                    //�Q�[���J�n�J�E���g�_�E����ʂɑJ��
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
                    //�n�C�X�R�A�N���A
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
            //�c�莞�Ԑݒ�
            Time = 3;
            //PlaySE(countdown3sec);
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            if(Time){
                //�c�莞�Ԃ��ς������SE��炷
                if(Time < lastTimeForPlaySE){
                    //PlaySE(1&2secSE)
                    //WriteBuffer(start countdown);
                }
            }
            //�c�莞��0�ŃQ�[������ʂɑJ��
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
            //�c�莞�Ԃ�60�ɐݒ�
            Time = 60;
            //WriteTobuffer(playing game);
            //BGM��炷
            //PlayBGM();
            SystemState.action = (uint8_t)DO;
            break;
        case DO:
            //�Q�[����
            if(Time){
                //���O���̏���
                MoleManager();
            }
            //�c�莞��0
            else{
                //BGM��~
                //StopBGM
                //���U���g��ʂɑJ��
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
            //SW5�������ꂽ��
            if(SWState == 0x10){
                //�n�C�X�R�A�X�V����
                if(Score>HighScore[Level-1]){
                    SaveHighScore(Level);
                }
                else{
                    //�������Ȃ�
                }
                //�^�C�g����ʂɑJ��
                ChangeState((uint8_t)TITLE);
                SystemState.action = (uint8_t)ENTRY;           
            }
            else{
                    //�������Ȃ�
            }
            break;
        default:
            break;
    }
}

