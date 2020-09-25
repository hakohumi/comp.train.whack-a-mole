#pragma once

#include <stdint.h>
#include <stdbool.h>

/* テストに使用する関数を記述 */
void AddRandSeed(uint16_t);

/* テストする関数を記述 */
uint16_t GetRand(void);

//モグラ出現時間取得関数
uint8_t GetPopTime(uint8_t, uint8_t);

//モグラ出現判定
bool PopDecision(uint16_t);