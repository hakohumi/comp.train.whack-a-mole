/* 
 * File:   Timer.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:10
 */

#include <stdint.h>

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

//残り時間
uint8_t Time;

//乱数規定�?�用時間
uint16_t TimeForRand;

/* ペナル�?ィ関数
 * ペナル�?ィを発生させる
 * 入�?
 * 出�? Time 残り時間
 */
void Penalty(void);

/* カウントダウン関数
 * カウントダウンを行う
 * 入�?
 * 出�? Time 残り時間
 */
void CountDown(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

