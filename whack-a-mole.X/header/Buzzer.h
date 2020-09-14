/*
 * File:   Buzzer.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:15 PM
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>

#include "Common.h"

#define REST 0
#define NOTE_LENGTH 0
#define NOTE_PITCH 1

void Buzzer_Initialize(void);
void UpdateBuzzer(void);

// LengthNote16thFlgを立てる
void Buzzer_SetLengthNote16thFlg(void);

uint16_t GetLengthNote16th_ms(void);

void PlayBuzzer(void);
void ChangePich(uint8_t i_Pich);

extern uint8_t PichTable[SCALE_NUM];

#endif /* BUZZER_H */
