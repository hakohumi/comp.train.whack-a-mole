/* 
 * File:   Time.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:10
 */

#ifndef TIME_H
#define	TIME_H

#ifdef	__cplusplus
extern "C" {
#endif

//残り時間
extern uint8_t Time;

//乱数規定値用時間
extern uint16_t TimeForRand;

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

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_H */

