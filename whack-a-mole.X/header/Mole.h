/* 
 * File:   Mole.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 17:34
 */

#ifndef MOLE_H
#define	MOLE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum MoleStateType_Type{
    HOLE,
    MOLE,
    HIT
} MoleStateType;

MoleStateType mole1;
MoleStateType mole2;
MoleStateType mole3;
MoleStateType mole4;

void OutOfHole(uint8_t);
void Attacked(uint8_t);
void BackToHole(uint8_t);

bool PopDecision(uint16_t);

#ifdef	__cplusplus
}
#endif

#endif	/* MOLE_H */

