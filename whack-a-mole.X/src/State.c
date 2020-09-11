#include "State.h"

void ChangeState(uint8_t i_displayState)
{
    MoleStrike.displayState = i_displayState;
}

void TitleProcess(void){
    switch(MoleStrike.action){
        case ENTRY:
            
            break;
        case DO:
            MoleStrike.displayState = SELECT_LEVEL;
            break;
        default:
            break;
    }
}

void SelectLevelProcess(void){
    switch(MoleStrike.action){
        case ENTRY:
            break;
        case DO:
            break;
        default:
            break;
    }
}

void HSClearProcess(void){
    switch(MoleStrike.action){
        case ENTRY:
            break;
        case DO:
            break;
        default:
            break;
    }
}

void StartCountDownProcess(void){
    switch(MoleStrike.action){
        case ENTRY:
            break;
        case DO:
            break;
        default:
            break;
    }
}

void PlayingGameProcess(void){
    switch(MoleStrike.action){
        case ENTRY:
            break;
        case DO:
            break;
        default:
            break;
    }
}

void ResultProcess(void){
    switch(MoleStrike.action){
        case ENTRY:
            break;
        case DO:
            break;
        default:
            break;
    }
}

