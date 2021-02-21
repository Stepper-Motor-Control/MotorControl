/**********************************************************************
* Filename    : Sweep.c
* Description : Servo sweep
* Author      : www.freenove.com
* modification: 2019/12/27
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>  
#include <string.h>       //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>       //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>     //FD_SET, FD_ISSET, FD_ZERO macros  
#include <iostream>
#include "Sensor.h"

#ifndef   TRUE    
#define TRUE   1
#endif

#ifndef  FALSE
#define FALSE  0
#endif

    
Sensor &mainSensor(int argc , char *argv[])   
{   

    std::cout << "Making a new program" << std::endl;
    std::cout << " ***** Dinesh Way to go*** " << std::endl;
    Sensor &m_Sensor = Sensor::GetInstance ();



   // m_Sensor.Wait();
     
    return m_Sensor;   
} 