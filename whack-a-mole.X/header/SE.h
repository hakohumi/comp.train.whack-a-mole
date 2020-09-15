/*
 * File:   SE.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:15 PM
 */

#ifndef SE_H
#define SE_H

#include <stdint.h>

#include "Common.h"

void SE_Initialize(void);
void PlaySE(void);

// SEの現在の再生位置
// uint16_t SE_GetPlayPos(void);

bool SE_GetIsPlay(void);

void SE_updateState(void);
void SE_updateManager(void);
void SE_returnBeginPlayPos(void);

#endif /* SE_H */
