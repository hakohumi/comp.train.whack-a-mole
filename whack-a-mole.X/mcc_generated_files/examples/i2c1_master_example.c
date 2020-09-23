/**
  I2C1 Generated Example Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1_master_example.c

  @Summary
    This is the generated driver examples implementation file for the I2C1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides implementations for driver APIs for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC16F1827
        Driver Version    :  1.0.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above or later
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

#include "i2c1_master_example.h"

typedef struct {
    size_t len;
    uint8_t *data;
} i2c1_buffer_t;


static i2c1_operations_t wr1RegCompleteHandler(void *ptr);
static i2c1_operations_t rdBlkRegCompleteHandler(void *ptr);

void I2C1_Write1ByteRegister(i2c1_address_t address, uint8_t reg, uint8_t data) {
    while (!I2C1_Open(address)); // sit here until we get the bus..
    I2C1_SetDataCompleteCallback(wr1RegCompleteHandler, &data);
    I2C1_SetBuffer(&reg, 1);
    I2C1_SetAddressNackCallback(NULL, NULL); //NACK polling?
    I2C1_MasterWrite();
    while (I2C1_BUSY == I2C1_Close()); // sit here until finished.
}

void I2C1_WriteNBytes(i2c1_address_t address, uint8_t* data, size_t len) {
    while (!I2C1_Open(address)); // sit here until we get the bus..
    I2C1_SetBuffer(data, len);
    I2C1_SetAddressNackCallback(NULL, NULL); //NACK polling?
    I2C1_MasterWrite();
    while (I2C1_BUSY == I2C1_Close()); // sit here until finished.
}

static i2c1_operations_t wr1RegCompleteHandler(void *ptr) {
    I2C1_SetBuffer(ptr, 1);
    I2C1_SetDataCompleteCallback(NULL, NULL);
    return I2C1_CONTINUE;
}
