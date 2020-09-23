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
} Player_t;

void Player_t_Init(Player_t *i_Player, uint8_t i_SM);

void returnBeginPlayPos(Player_t *i_Player);
void updatePlayerState(Player_t *i_Player);
void updatePlayerManager(Player_t *i_Player);

#endif /* PLAYER_H */
