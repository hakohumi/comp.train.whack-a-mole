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

extern uint16_t HighScore[3];
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
 * 出力 HighScore[難易度-1]
 */
void SaveHighScore(uint8_t);

/* ハイスコアクリア関数
 * 指定された難易度のHighScoreを0クリアする
 * 入力
 * 出力 HighScore[難易度-1]
 */
void ClearHighScore(uint8_t);

#ifdef __cplusplus
}
#endif

#endif /* SCORE_H */
