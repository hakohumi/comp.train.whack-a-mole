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

#define LED1 LATAbits.LATA0
#define LED2 LATAbits.LATA1
#define LED3 LATAbits.LATA2
#define LED4 LATAbits.LATA3
#define LED5 LATAbits.LATA4
#define LED6 LATAbits.LATA6
#define LED7 LATAbits.LATA7
#define LED8 LATBbits.LATB7

void UpdateLED(uint8_t i_LEDbits);
void LED_AllOff(void);

#endif /* LED_H */
