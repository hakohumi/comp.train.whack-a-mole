/* 
 * File:   Input.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:13
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef INPUT_H
#define	INPUT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum SWPortPosType_Type{
        SW1 = 0x01,
        SW2 = 0x02,
        SW3 = 0x04,
        SW4 = 0x10,
        SW5 = 0x40
    } SWPortPosType;

//SW構�??�?
typedef struct {
    bool isPushed;
    bool lastPushed;
    uint8_t valueForCompareSW;
    uint8_t chattCount;
} SWType;

//SW1-5
extern SWType sw1 = { 0, 0, (uint8_t)SW1, 0};
extern SWType sw2 = { 0, 0, (uint8_t)SW2, 0};
extern SWType sw3 = { 0, 0, (uint8_t)SW3, 0};
extern SWType sw4 = { 0, 0, (uint8_t)SW4, 0};
extern SWType sw5 = { 0, 0, (uint8_t)SW5, 0};

//ポ�?�ト�?�入力�?�(�?工)
uint8_t InputPort;

//SW入力状�?
uint8_t SWState;

//
void DetectPushSW(void);

//
void detectPushSWX(SWType*); 

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */

