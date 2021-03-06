#include "Rand.h"

#include "memory.h"

// 16bit シード値
static uint16_t seedX = 1, seedY = 1;

// EEPROMからシード値を取ってくる
void RandInitialize(void) {
    seedX = DATAEE_ReadByte(EEPROM_ADDR_RAND_SEEDX_VALUE);
    seedY = DATAEE_ReadByte(EEPROM_ADDR_RAND_SEEDY_VALUE);
}

// EEPROMにシード値を格納する
void SaveRandSeed(void) {
    DATAEE_WriteByte(EEPROM_ADDR_RAND_SEEDX_VALUE, seedX);
    DATAEE_WriteByte(EEPROM_ADDR_RAND_SEEDY_VALUE, seedY);
}

// 16bitのxorshiftを使った乱数発生関数

uint16_t GetRand(void) {
    uint16_t t   = (seedX ^ (seedX << 5));
    
    seedX        = seedY;
    return seedY = (seedY ^ (seedY >> 1)) ^ (t ^ (t >> 3));
}

// 現在のシード値に引数で指定された数値を追加する
void AddRandSeed(uint16_t i_val) {
    seedY += i_val;
}

/* -------------------------------------------------- */
