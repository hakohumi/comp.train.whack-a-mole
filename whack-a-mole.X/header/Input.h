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

//SW\‘¢‘Ì
typedef struct {
    uint8_t chattCount;
    uint8_t valueForCompareSW;
    bool isPushed;
    bool lastPushed;
} SWType;

//SW1-5
SWType sw1 = { 0, 0x01, 0, 0};
SWType sw2 = { 0, 0x02, 0, 0};
SWType sw3 = { 0, 0x04, 0, 0};
SWType sw4 = { 0, 0x08, 0, 0};
SWType sw5 = { 0, 0x10, 0, 0};

//DetectPushSW‚Ì“ü—Í’l(‰ÁH)
uint8_t InputPort;

//SW“ü—Íó‘Ô
uint8_t SWState;

//
void DetectPushSW(void);

//
void detectPushSWX(SWType*); 

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */

