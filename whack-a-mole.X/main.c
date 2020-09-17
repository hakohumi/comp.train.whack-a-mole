/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules
  selected in the GUI. Generation Information : Product Revision  :  PIC10 /
  PIC12 / PIC16 / PIC18 MCUs - 1.81.4 Device            :  PIC16F1827 Driver
  Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software
   and any derivatives exclusively with Microchip products. It is your
   responsibility to comply with third party license terms applicable to your
   use of third party software (including open source software) that may
   accompany Microchip software.

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

#include <string.h>

#include "Common.h"
#include "LCD.h"
#include "LED.h"
#include "Rand.h"
#include "_Mole.h"
#include "mcc.h"

// マイコンに書き込み時にEEPROMに値を書き込む
// 8バイトずつ
// __EEPROM_DATA(0, 2, 4, 6, 7, 5, 3, 1);

// global variable

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // LCD初期化
    LCDInitialize();
    // LCDをON
    DisplayON();

    // LCDのバッファ
    uint8_t *l_str  = "LCD";
    uint8_t *l_str2 = "test";

    // 乱数保存用
    uint16_t rand = 0;

    while (1) {
        // 乱数発生
        // rand = GetRand();

        //         ItoStr(rand, &l_str, 8);

        // デバッグ用のLED表示
        // UpdateLED(rand);

        // l_strに入っている文字列をバッファへ書き込む
        // strlenで文字列の文字数を取得している、
        WriteToBufferFirst(l_str, strlen(l_str));

        WriteToBufferTime((uint8_t)rand++);
        WriteToBufferScore(rand + rand);
        WriteToBufferMole(1, HOLE);
        WriteToBufferMole(2, MOLE);
        WriteToBufferMole(3, MOLE);
        WriteToBufferMole(4, HIT);

        BufferToLCD();
        __delay_ms(500);
    }
}

/**
     End of File
 */
