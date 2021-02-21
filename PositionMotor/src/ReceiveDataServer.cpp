/**********************************************************************
* Filename    : Sweep.c
* Description : Servo sweep
* Author      : www.freenove.com
* modification: 2019/12/27
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>  
#include <string.h>   //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
#include "PositionServoMotor.h"
     
#ifndef   TRUE    
#define TRUE   1
#endif

#ifndef  FALSE
#define FALSE  0
#endif

    
int main(int argc , char *argv[])   
{   
    PositionServoMotor *pPositionServoMotor  =  new PositionServoMotor();

    Comms *pComms = reinterpret_cast<Comms*> (pPositionServoMotor);
    pComms->Init();

    pComms->Wait();
    delete pPositionServoMotor;
    return 0;   
} 