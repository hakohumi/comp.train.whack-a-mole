#include "State.h"

void ChangeState(uint8_t i_displayState)
{
    systemState.displayState = i_displayState;
}

void TitleProcess(void){
    switch(systemState.action){
        case ENTRY:
            systemState.action = DO;
            break;
        case DO:
            systemState.displayState = SELECT_LEVEL;
            SystemState.action = ENTRY;
            break;
        default:
            break;
    }
}

void SelectLevelProcess(void){
    switch(systemState.action){
        case ENTRY:
            systemState.action = DO;
            break;
        case DO:
            systemState.displayState = HS_CLEAR;
            SystemState.action = ENTRY;
            
            systemState.displayState = START_COUNT_DOWN;
            SystemState.action = ENTRY;
            break;
        default:
            break;
    }
}

void HSClearProcess(void){
    switch(systemState.action){
        case ENTRY:
            systemState.action = DO;
            break;
        case DO:
            systemState.displayState = SELECT_LEVEL;
            SystemState.action = ENTRY;
            break;
        default:
            break;
    }
}

void StartCountDownProcess(void){
    switch(systemState.action){
        case ENTRY:
            systemState.action = DO;
            break;
        case DO:
            systemState.displayState = PLAYING_GAME;
            SystemState.action = ENTRY;
            break;
        default:
            break;
    }
}

void PlayingGameProcess(void){
    switch(systemState.action){
        case ENTRY:
            systemState.action = DO;
            break;
        case DO:
            systemState.displayState = RESULT;
            SystemState.action = ENTRY;
            break;
        default:
            break;
    }
}

void ResultProcess(void){
    switch(systemState.action){
        case ENTRY:
            systemState.action = DO;
            break;
        case DO:
            systemState.displayState = TITLE;
            SystemState.action = ENTRY;
            break;
        default:
            break;
    }
}

