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

//SWæ§‹é??ä½?
typedef struct {
    bool isPushed;
    bool lastPushed;
    uint8_t valueForCompareSW;
    uint8_t chattCount;
} SWType;

//SW1-5
SWType sw1 = { 0, 0, 0};
SWType sw2 = { 0, 0, 0};
SWType sw3 = { 0, 0, 0};
SWType sw4 = { 0, 0, 0};
SWType sw5 = { 0, 0, 0};

//ãƒã?¼ãƒˆã?®å…¥åŠ›å?¤(åŠ?å·¥)
uint8_t InputPort;

//SWå…¥åŠ›çŠ¶æ…?
uint8_t SWState;

//
void detectPushSW(void);

//
void detectPushSWX(SWType*); 

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */

