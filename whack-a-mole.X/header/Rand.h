/*
 * File:   Rand.h
 * Author: fuminori.hakoishi
 *
 * Created on 2020/09/04, 16:03
 */

#ifndef RAND_H
#define RAND_H

#include <stdint.h>

// Rand関数を初期化
void RandInitialize(void);

// Randのシード値をEEPROMに格納する
void SaveRandSeed(void);

// 16bitのxorshiftを使った乱数発生関数
uint16_t GetRand(void);

// 現在のシード値に引数で指定された数値を追加する
void AddRandSeed(uint16_t i_val);

#ifdef NOUSE

// 16bitのxorshiftのシード値を設定する
void SetRandSeed(uint16_t x, uint16_t y);
// 16bitのxorshiftのシードXの値を取得する
uint16_t GetRandSeedX(void);
// 16bitのxorshiftのシードYの値を取得する
uint16_t GetRandSeedY(void);

/* -------------------------------------------------- */

// 32bit 乱数発生器
// ※実験用
uint32_t GetRand32(void);

/* -------------------------------------------------- */
#endif

#endif /* RAND_H */
