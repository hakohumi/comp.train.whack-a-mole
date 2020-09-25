#include "test.h"

/* テストに使用する変数を記述 */
// 16bit シード値
static uint16_t seedX = 1, seedY = 1;

/**************************************/

/* テストに使用する関数を記述 */
//シード値を変更する関数
void AddRandSeed(uint16_t i_val) {
    seedY += i_val;
}

/******************************/

/* テストする関数を記述 */
//乱数取得関数
uint16_t GetRand(void) {
    uint16_t t = (seedX ^ (seedX << 5));

    seedX = seedY;
    return seedY = (seedY ^ (seedY >> 1)) ^ (t ^ (t >> 3));
}

//モグラ表示時間取得関数
uint8_t GetPopTime(uint8_t i_level, uint8_t i_time) {
    uint8_t minPopTime;
    uint8_t maxPopTime;
    uint8_t retVal;

    if (i_level <= 2) {
        minPopTime = 100 >> (i_level);
        maxPopTime = 50 * (4 - i_level);
    }
    else {
        minPopTime = 0;
        maxPopTime = 0;
    }
    if (i_time <= 60) {
        retVal = minPopTime + ((maxPopTime - minPopTime) / 60) * i_time;
    }
    else {
        retVal = 0;
    }
    return retVal;
}

//モグラ出現判定
bool PopDecision(uint16_t i_decisionNumber) {
    bool retVal = false;

    if (GetRand() < i_decisionNumber) {
        retVal = true;
    }
    return retVal;
}