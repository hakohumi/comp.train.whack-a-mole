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

void Buzzer_Initialize(void);
void UpdateBuzzer(void);
void UpdateBGMManager(void);
void UpdateSEManager(void);

// BGMの現在の再生位置
uint16_t GetBGMPlayPos(void);

// LengthNote16thFlgを立てる
void Buzzer_SetLengthNote16thFlg(void);

#endif /* BUZZER_H */
