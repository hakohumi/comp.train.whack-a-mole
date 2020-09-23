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

#include "Buzzer.h"
#include "Common.h"
#include "Input.h"
#include "LCD.h"
#include "Rand.h"
#include "Score.h"
#include "State.h"
#include "Timer.h"
#include "mcc.h"

// マイコンに書き込み時にEEPROMに値を書き込む
// 8バイトずつ
//__EEPROM_DATA(0, 1, 2, 3, 4, 5, 6, 7);
//__EEPROM_DATA(8, 9, 10, 11, 12, 13, 14, 15);

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral
    // Interrupt Enable bits Use the following macros to:

    // Myfunction init
    Buzzer_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    //初期化処理
    ChangeState(TITLE);
    SystemState.action = ENTRY;
    SWState            = 0;

    // 乱数の初期化
    RandInitialize();

    // LCD初期化
    LCDInitialize();
    // LCDをON
    DisplayON();

    // PlayBGM();

    while (0) {
        //状態処理
        switch (SystemState.displayState) {
            //タイトル画面
            case TITLE:
                TitleProcess();
                break;
            //難易度選択画面
            case SELECT_LEVEL:
                SelectLevelProcess();
                break;
            //ハイスコアクリア確認画面
            case HS_CLEAR:
                HSClearProcess();
                break;
            //ゲーム開始カウントダウン画面
            case START_COUNT_DOWN:
                StartCountDownProcess();
                break;
            //ゲーム中画面
            case PLAYING_GAME:
                PlayingGameProcess();
                break;
            //リザルト画面
            case RESULT:
                ResultProcess();
                break;
            default:
                break;
        }

        // LCD更新
        BufferToLCD();
        UpdateBuzzer();
    }
}

#ifdef NOUSE
// マイコンに書き込み時にEEPROMに値を書き込む
// 8バイトずつ
//__EEPROM_DATA(0, 1, 2, 3, 4, 5, 6, 7);
//__EEPROM_DATA(8, 9, 10, 11, 12, 13, 14, 15);

void wirtePichTableToEEPROM(void) {
    uint8_t c;
    uint8_t PichTable[SCALE_NUM] = {
        0x00,  // REST
        0xEE,  // DO
        0xE1,  // DO_SHARP
        0xD4,  // RE
        0xC8,  // RE_SHARP
        0xBD,  // MI
        0xB2,  // FA
        0xA8,  // FA_SHARP
        0x9F,  // SO
        0x96,  // SO_SHARP
        0x8E,  // RA
        0x86,  // RA_SHARP
        0x7E,  // SI
        0x77,  // DO2
        0x6A,  // RE2
        0x5E,  // MI2
        0x59,  // FA2
        0x4F,  // SO2
        0x47,  // RA2
        0x3F   // SI2

    };

    for (c = 0; c < SCALE_NUM; c++) {
        DATAEE_WriteByte(EEPROM_ADDR_SHEETMUSIC_REST + c, PichTable[c]);
    }
}

#endif
/**
     End of File
 */
