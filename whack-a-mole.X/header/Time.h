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

uint8_t Time;
uint16_t TimeForRand;

void Penalty(void);
void CountDown(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_H */

