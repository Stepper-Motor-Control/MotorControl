/**********************************************************************
 * Description
 *  The Ultrasonic Ranging Module uses the principle that ultrasonic 
 * waves will reflect when they encounter any obstacles. This is 
 * possible by counting the time interval between when the ultrasonic 
 * wave is transmitted to when the ultrasonic wave reflects back after 
 * encountering an obstacle. Time interval counting will end after
 * an ultrasonic wave is received, and the time difference (delta) is 
 * the total time of the ultrasonic wave’s journey from being transmitted 
 * to being received. Because the speed of sound in air is a constant, 
 * and is about v=340m/s, we can calculate the distance between the 
 * Ultrasonic Ranging Module and the obstacle: distance = (velocity * time)/2. 
 * 
 *   |<-----Distance------------------>|
 *   |---- Sent trigger 10 microsec -->| 
 *   |-------------------------------->|
 *   |<--------------------------------|
 *   |<-------- distance ------------->|      
 * distance = pingTime*340.0/ 2.0 / 10000.0; //calculate distance with sound speed
340m/s  
 * 
**********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>
#include <time.h>
#include "LcdDisplay.h"

int32_t LcdDisplay::ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize)
{
    std::cout << "This function needs to be implimented" << std::endl;
    return 0;
}


int32_t LcdDisplay::detectI2C(int32_t addr)
{
    int _fd = wiringPiI2CSetup (addr);   
    if (_fd < 0){		
        printf("Error address : 0x%x \n",addr);
        return 0 ;
    } 
    else{	
        if(wiringPiI2CWrite(_fd,0) < 0){
            printf("Not found device in address 0x%x \n",addr);
            return 0;
        }
        else{
            printf("Found device in address 0x%x \n",addr);
            return 1 ;
        }
    }
}

void LcdDisplay::Display(const char *pData, int32_t line) 
{
    char dispData[15];
    memset (dispData, 0, sizeof(dispData));

    if (pData == NULL)
    {
        return ;
    }

    snprintf(dispData,sizeof(dispData),"%s",pData);

    if (line == 0)
    {
        // set the LCD cursor position to (0,0) 
        lcdPosition(m_LcdHandler,0,0);
    }
    else
    {
        // set the LCD cursor position to (0,1) 
        lcdPosition(m_LcdHandler,0,1);
    }

    lcdPrintf(m_LcdHandler,"%s",dispData); //Display system time on LCD
    
}


LcdDisplay::LcdDisplay(void) : m_debug(true) 
{
   printf("Starting comms interface %s::Init...\n",__FUNCTION__,__LINE__);
   Comms::Init(PORT_TO_CONNECT);

   if( detectI2C( PCF8574_ADDRESS_3F) )
   {
        m_pcf8574_Address = PCF8574_ADDRESS_3F;
   }
   else if( detectI2C(PCF8574_ADDRESS_27) )
   {
       m_pcf8574_Address = PCF8574_ADDRESS_27;
   }
   else
   {
       m_pcf8574_Address = 0;
       printf("No correct I2C address found, \n"
       "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
       "Program Exit. \n");
   }

    //initialize PCF8574
    pcf8574Setup(BASE,m_pcf8574_Address);

    for(int i = 0; i < 8 ;  i++)
    {
        pinMode(BASE+i , OUTPUT);     //set PCF8574 port to output mode
    } 
    digitalWrite(LED,HIGH);     //turn on LCD backlight
    digitalWrite(RW,LOW);       //allow writing to LCD
    // initialize LCD and return “handle” used to handle LCD
	
    if((m_LcdHandler = lcdInit(2,16,4,RS,EN,D4,D5,D6,D7,0,0,0,0)) == -1)
    {
        printf("lcdInit failed !");
    }

}

LcdDisplay::~LcdDisplay(void)
{

}



