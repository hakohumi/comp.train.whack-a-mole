/* 
 * File:   Level.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:37
 */

#ifndef LEVEL_H
#define	LEVEL_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum LevelType_Type{
    EASY = 1,
    NORMAL,
    HARD,
}LevelType;

uint8_t Level;

void SetLevel(uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* LEVEL_H */

