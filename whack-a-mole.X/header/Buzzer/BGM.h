/*
 * File:   BGM.h
 * Author: fuminori.hakoishi
 *
 * Created on September 4, 2020, 4:15 PM
 */

#ifndef BGM_H
#define BGM_H

#include <stdint.h>

#include "Common.h"

void BGM_Initialize(void);
void PlayBGM(void);

bool GetIsPlayBGM(void);

void updateBGMState(void);
void updateBGMManager(void);
void BGM_returnBeginPlayPos(void);

#endif /* BGM_H */
