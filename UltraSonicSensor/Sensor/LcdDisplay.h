
#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>
#include <time.h>
#include "Comms.h"

using namespace std;

class LcdDisplay : public Comms
{
public:
    LcdDisplay(void) ;
    ~LcdDisplay(void);

    void Display(const char *pData, int32_t line) ;
    
private:
    uint32_t m_debug;
    static const int32_t PORT_TO_CONNECT = 8890;
    int32_t ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize);


    static const int32_t PCF8574_ADDRESS_27 = 0x27;      // PCF8574T:0x27, PCF8574AT:0x3F
    static const int32_t PCF8574_ADDRESS_3F = 0x3F;      // PCF8574T:0x27, PCF8574AT:0x3F
    
    static const int32_t BASE            = 64;        // BASE any number above 64
    //Define the output pins of the PCF8574, which are directly connected to the LCD1602 pin.
    static const int32_t RS              = BASE+0;
    static const int32_t RW              = BASE+1;
    static const int32_t EN              = BASE+2;
    static const int32_t LED             = BASE+3;
    static const int32_t D4              = BASE+4;
    static const int32_t D5              = BASE+5;
    static const int32_t D6              = BASE+6;
    static const int32_t D7              = BASE+7;
    
    int32_t    m_LcdHandler;
    int32_t    m_pcf8574_Address;

    int32_t detectI2C(int32_t addr);
    

 
};

#endif