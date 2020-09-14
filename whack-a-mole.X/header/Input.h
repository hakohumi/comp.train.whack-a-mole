/* 
 * File:   Input.h
 * Author: tomohiro.sasaki
 *
 * Created on 2020/09/11, 16:13
 */

#include <stdint.h>

#ifndef INPUT_H
#define	INPUT_H

#ifdef	__cplusplus
extern "C" {
#endif

//SW�\����
typedef struct {
    uint8_t isPushed;
    uint8_t lastPushed;
    uint8_t chattCount;
} SWType;

//SW1-5
SWType sw1 = { 0, 0, 0};
SWType sw2 = { 0, 0, 0};
SWType sw3 = { 0, 0, 0};
SWType sw4 = { 0, 0, 0};
SWType sw5 = { 0, 0, 0};

//�|�[�g�̓��͒l(���H)
uint8_t InputPort;

//SW���͏��
uint8_t SWState;

//
void detectPushSW(void);

//
void detectPushSWX(SWType*); 

#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_H */

