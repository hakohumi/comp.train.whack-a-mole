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
void PlayBGM(void);
void UpdateBuzzer(void);

// BGMの現在の再生位置
uint16_t GetBGMPlayPos(void);

// LengthNote16thFlgを立てる
void Buzzer_SetLengthNote16thFlg(void);
bool GetIsPlayBGM(void);
bool GetIsPlaySE(void);
uint16_t GetLengthNote16th_ms(void);

typedef enum {
    DO,
    DO_SHARP,
    RE,
    RE_SHARP,
    MI,
    FA,
    FA_SHARP,
    SO,
    SO_SHARP,
    RA,
    RA_SHARP,
    SI,
    DO2,
    RE2,
    MI2,
    FA2,
    SO2,
    RA2,
    SI2,
    SCALE_NUM

} ScaleType;

#endif /* BUZZER_H */
