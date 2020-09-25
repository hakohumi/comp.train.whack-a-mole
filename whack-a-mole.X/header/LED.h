/*
 * File:   LED.h
 * Author: fuminori.hakoishi
 *
 * Created on 2020/09/04, 15:28
 */

#ifndef LED_H
#define LED_H

#include <stdint.h>

#include "mcc.h"

#define LED_ON 0
#define LED_OFF 1

#define LED1 LATBbits.LATB2
#define LED2 LATBbits.LATB3
#define LED3 LATBbits.LATB5
#define LED4 LATBbits.LATB6
#define LED5 LATBbits.LATB7
#define LED6 LATAbits.LATA7
// #define LED7 LATBbits.LATB7
// #define LED8 LATBbits.LATB7

void UpdateLED(uint8_t i_LEDbits);
void LED_AllOff(void);

#endif /* LED_H */
