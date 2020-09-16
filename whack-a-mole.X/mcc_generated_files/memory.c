/**
  MEMORY Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    memory.c

  @Summary
    This is the generated driver implementation file for the MEMORY driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations of driver APIs for MEMORY.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC16F1827
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB             :  MPLAB X 5.40
 */

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

/**
  Section: Included Files
 */

#include <xc.h>
#include "memory.h"

/**
  Section: Flash Module APIs
 */

/**
  Section: Data EEPROM Module APIs
 */

void DATAEE_WriteByte(uint8_t bAdd, uint8_t bData) {
    uint8_t GIEBitValue = 0;

    EEADRL = (uint8_t)(bAdd & 0x0ff); // Data Memory Address to write
    EEDATL = bData; // Data Memory Value to write
    EECON1bits.EEPGD = 0; // Point to DATA memory
    EECON1bits.CFGS = 0; // Deselect Configuration space
    EECON1bits.WREN = 1; // Enable writes

    GIEBitValue = INTCONbits.GIE;
    INTCONbits.GIE = 0; // Disable INTs
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1; // Set WR bit to begin write
    // Wait for write to complete
    while (EECON1bits.WR) {
    }

    EECON1bits.WREN = 0; // Disable writes
    INTCONbits.GIE = GIEBitValue;
}

uint8_t DATAEE_ReadByte(uint8_t bAdd) {
    EEADRL = (uint8_t)(bAdd & 0x0ff); // Data Memory Address to read
    EECON1bits.CFGS = 0; // Deselect Configuration space
    EECON1bits.EEPGD = 0; // Point to DATA memory
    EECON1bits.RD = 1; // EE Read
    NOP(); // NOPs may be required for latency at high frequencies
    NOP();

    return (EEDATL);
}
/**
 End of File
 */