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
#include "SheetMusic.h"

#define REST 0
#define NOTE_LENGTH 0
#define NOTE_PITCH 1

/* -------------------------------------------------- */
// mainで呼ばれる関数
/* -------------------------------------------------- */

// 初期化
void Buzzer_Initialize(void);
// ブザーの処理
void UpdateBuzzer(void);

/* -------------------------------------------------- */

// BGM.c,SE.cで呼ばれる
void PlayBuzzer(void);
void ChangePich(uint8_t i_Pich);
void SM_ChangePich(SheetMusic_t *i_SheetMusic, uint16_t i_pos);
uint16_t Change10msLength(uint8_t i_NoteLength, uint16_t i_Tempo);


void SetUpdate10msBuzzerFlg(void);

extern uint8_t PichTable[SCALE_NUM];

#endif /* BUZZER_H */
