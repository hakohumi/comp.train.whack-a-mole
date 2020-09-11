/* 
 * File:   Score.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:57
 */

#ifndef SCORE_H
#define	SCORE_H

#ifdef	__cplusplus
extern "C" {
#endif

uint16_t HighScore[3];
uint16_t Score;

void IncScore(void);
void SaveHighScore(void);
void ClearHighScore(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SCORE_H */

