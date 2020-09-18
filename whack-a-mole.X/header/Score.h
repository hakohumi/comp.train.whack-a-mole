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

/* スコア加算関数
 * Scoreを1増加する
 * 入力
 * 出力 Score(最大999)
 */
void IncScore(void);

/* ハイスコア記録関数
 * 指定された難易度のHighScoreをScoreの値で記録する
 * 入力 Score
 * 出力 void
 */
void SaveHighScore(uint8_t i_level, uint16_t i_score);

/* ハイスコアクリア関数
 * 指定された難易度のHighScoreを0クリアする
 * 入力 難易度
 * 出力 void
 */
// void ClearHighScore(uint8_t i_level);

/* ハイスコア取得関数
 * 指定された難易度のHighScoreをEEEPROMから取得する
 * 入力 難易度
 * 出力 HighScore uint16_t
 */

uint16_t GetHighScore(uint8_t i_level);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
