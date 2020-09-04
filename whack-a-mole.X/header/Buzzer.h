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

#endif /* BUZZER_H */
