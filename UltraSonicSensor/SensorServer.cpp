/**********************************************************************
* Filename    : SensorServer.cpp.c
* Description : Servo sweep
* Author      : Dinesh Trikha 
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
#include "SensorCommsServer.h"
#include "Sensor.h"

#ifndef   TRUE    
#define TRUE   1
#endif

#ifndef  FALSE
#define FALSE  0
#endif

extern Sensor & mainSensor(int argc , char *argv[])   ;
    
int main(int argc , char *argv[])   
{   

    std::cout << "Making a new program" << std::endl;
    std::cout << " ***** Dinesh Way to go*** " << std::endl;

    Sensor &localSensor = mainSensor( argc, argv) ;

    SensorCommsServer  *pSensorCommsServer = new SensorCommsServer(localSensor);

 
    localSensor.Wait();
    pSensorCommsServer->Wait();

    delete pSensorCommsServer;

     
    return 0;   
} 