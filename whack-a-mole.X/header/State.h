/* 
 * File:   State.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 14:50
 */

#ifndef STATE_H
#define	STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum DisplayStateType_Type{
    TITLE,
    SELECT_LEVEL,
    HS_CLEAR,
    START_COUNT_DOWN,
    PLAYING_GAME,
    RESULT
} DisplayStateType;

typedef enum ActionType_Type{
    ENTRY,
    DO
} ActionType;

typedef struct {
    uint8_t displayState;
    uint8_t action;
} SystemState;

SystemState systemState;

void ChangeState(uint8_t);
void TitleProcess(void);
void SelectLevelProcess(void);
void HSClearProcess(void);
void StartCountDownProcess(void);
void PlayingGameProsess(void);
void ResultProcess(void);

#ifdef	__cplusplus
}
#endif

#endif	/* STATE_H */

