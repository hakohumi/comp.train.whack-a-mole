/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC16F1827
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third
   party license terms applicable to your use of third party software (including open source
   software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

// global variable

// randで0~7の間で出力された値を格納する変数
// 1秒タイマで操作
uint8_t RandLED = 0;

void UpdateLED();
void LED_AllOff();

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    // INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    // INTERRUPT_PeripheralInterruptDisable();

    while (1) {
        // Add your application code

        UpdateLED();
    }
}

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

// RandLEDの値から、対応したLEDを表示させる

void UpdateLED() {
    LED_AllOff();

    switch (RandLED) {
        case 0:
            LED1 = LED_ON;
            break;
        case 1:
            LED2 = LED_ON;
            break;
        case 2:
            LED3 = LED_ON;
            break;
        case 3:
            LED4 = LED_ON;
            break;
        case 4:
            LED5 = LED_ON;
            break;
        case 5:
            LED6 = LED_ON;
            break;
        case 6:
            LED7 = LED_ON;
            break;
        case 7:
            LED8 = LED_ON;
            break;
    }
}

void LED_AllOff() {
    LED1 = LED_OFF;
    LED2 = LED_OFF;
    LED3 = LED_OFF;
    LED4 = LED_OFF;
    LED5 = LED_OFF;
    LED6 = LED_OFF;
    LED7 = LED_OFF;
    LED8 = LED_OFF;
}
/**
 End of File
 */