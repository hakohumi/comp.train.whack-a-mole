/**
  MEMORY Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    memory.h

  @Summary
    This is the generated header file for the MEMORY driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for MEMORY.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC16F1827
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB             :  MPLAB X 5.40
 *******************************************************************************/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
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

#ifndef MEMORY_H
#define MEMORY_H

/**
  Section: Included Files
 */

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif

/**
      Section: Macro Declarations
     */

#define WRITE_FLASH_BLOCKSIZE 8
#define ERASE_FLASH_BLOCKSIZE 32
#define END_FLASH 0x1000

void DATAEE_WriteByte(uint8_t bAdd, uint8_t bData);

/**
      @Summary
        Reads a data byte from Data EEPROM

      @Description
        This routine reads a data byte from given Data EEPROM location

      @Preconditions
        None

      @Param
        bAdd  - Data EEPROM location from which data has to be read

      @Returns
        Data byte read from given Data EEPROM location

      @Example
        <code>
        uint8_t dataeeAddr = 0x10;
        uint8_t readData;

        readData = DATAEE_ReadByte(dataeeAddr);
        </code>
     */
uint8_t DATAEE_ReadByte(uint8_t bAdd);

/* -------------------------------------------------- */
// EEPROMの予約リスト
// アドレス 0 ~ 255
// データ幅 8bit
/* -------------------------------------------------- */
typedef enum {
    EEPROM_ADDR_ERROR,
    EEPROM_ADDR_HIGHSCORE_EASY_H,
    EEPROM_ADDR_HIGHSCORE_EASY_L,
    EEPROM_ADDR_HIGHSCORE_NORMAL_H,
    EEPROM_ADDR_HIGHSCORE_NORMAL_L,
    EEPROM_ADDR_HIGHSCORE_HARD_H,
    EEPROM_ADDR_HIGHSCORE_HARD_L,
    EEPROM_ADDR_RAND_SEEDX_VALUE,
    EEPROM_ADDR_RAND_SEEDY_VALUE
} EEPROMListType;

#ifdef __cplusplus  // Provide C++ Compatibility
}

#endif

#endif  // MEMORY_H
/**
 End of File
 */
