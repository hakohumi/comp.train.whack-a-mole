/*
 * File:   Score.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:57
 */

#include <stdint.h>

#ifndef SCORE_H
#define SCORE_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint16_t Score;

/* スコア増加関数
 * Scoreを1増加する
 * 入力
 * 出力 uint16_t Score(最大値999)
 */
void IncScore(void);

/* ハイスコア保存関数
 * 指定された難易度のハイスコアをEEPROMに保存する
 * 入力 uint8_t i_level ゲームの難易度
 *     uint16_t i_score スコア
 * 出力 
 */
void SaveHighScore(uint8_t i_level, uint16_t i_score);

/* ハイスコア取得関数
 * EEEPROMから指定された難易度のハイスコアを取得する
 * 入力 uint8_t i_level ゲームの難易度
 * 出力 uint16_t HighScore ハイスコア
 */
uint16_t GetHighScore(uint8_t i_level);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
