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

#endif /* RAND_H */
