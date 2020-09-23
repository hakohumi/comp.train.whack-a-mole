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

/* -------------------------------------------------- */
// mainで呼ばれる関数
/* -------------------------------------------------- */

// 初期化
void Buzzer_Initialize(void);
// ブザーの処理
void UpdateBuzzer(void);

/* -------------------------------------------------- */

// Player.h

typedef struct {
    uint16_t currentNoteLength;  // 音符中の再生位置
    bool IsPlay;                 // 再生中フラグ
    bool StartFlg;               // 再生開始フラグ
} Player_t;

void updatePlayerState(void);
void updatePlayerManager(void);

void SetUpdate10msBuzzerFlg(void);

void PlaySE(void);
void SE_updatePlayerManager(void);

extern uint16_t Buzzer10msFlg;

#endif /* BUZZER_H */
