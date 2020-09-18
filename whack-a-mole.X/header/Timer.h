/* 
 * File:   Timer.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:10
 */

#include <stdint.h>

#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* ペナルティ関数
 * ペナルティを発生させる
 * 入力
 * 出力 Time 残り時間
 */
void Penalty(void);

/* カウントダウン関数
 * カウントダウンを行う
 * 入力
 * 出力 Time 残り時間
 */
void CountDown(void);

extern uint8_t RemaingTime;
extern uint16_t TimeForRand;

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H */
