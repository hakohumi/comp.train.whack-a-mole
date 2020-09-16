/*
 * File:   BGM.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:15 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

#include "Common.h"
#include "SheetMusic.h"

// BGM・SEの構造体

typedef struct {
    SheetMusic_t *SheetMusic;    // 再生する楽譜
    uint16_t PlayNotePos;        // 再生位置
    uint16_t EndPos;             // 終端位置
    uint16_t currentNoteLength;  // 音符中の再生位置
    bool IsPlay;                 // 再生中フラグ
    bool StartFlg;               // 再生開始フラグ
    bool StopFlg;                // 停止開始フラグ
} Player_t;

void Player_Initialize(void);
void PlayBGM(void);
void PlaySE(void);

void returnBeginPlayPos(Player_t *i_Player);
void updatePlayerState(Player_t *i_Player);
void BGM_updatePlayerState(void);
void SE_updatePlayerState(void);
void updatePlayerManager(Player_t *i_Player);
void BGM_updatePlayerManager(void);
void SE_updatePlayerManager(void);

void BGM_ChangeCurrentPich(void);
bool GetIsPlayBGM(void);
bool GetIsPlaySE(void);

#endif /* PLAYER_H */
