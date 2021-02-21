

#ifndef  SENSOR_COMMS_SERVER_H
#define  SENSOR_COMMS_SERVER_H

#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <mqueue.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <errno.h>
#include "Comms.h"
#include "Client.h"
#include "Sensor.h"
#include "LcdDisplay.h"
#include "StepperMotor.h"

using namespace std;


class SensorCommsServer 
{
public:
   // SensorCommsServer() ;
    SensorCommsServer(Sensor & sensor);
    ~SensorCommsServer(void);
  

   bool GetStatus(void)
   {
       return m_Status;
   }

   void SetStatus(bool status)
   {
       m_Status = status;
   }

   int32_t Wait(void);

   Client *m_pClientCommsTcp;

   double GetDistance(void) { return m_refSensor.GetDistance();}

   void DispData(const char *pData, int32_t line);
private:
    
    uint32_t m_debug;
    bool m_Status;
 
   void Lock(void) 
   {
       pthread_mutex_lock(&m_lock);
   }

   void UnLock(void) 
   {
       pthread_mutex_unlock(&m_lock);
   }

    // Parameters for creating threads
    pthread_mutex_t m_lock;
    pthread_attr_t  m_attr;
    pthread_t       m_threads;
    static void *ProcessData(void *pContext);
    static const int32_t PORT_TO_CONNECT = 8889;
    Sensor & m_refSensor;  

    LcdDisplay    *m_pLcdDisplay; 
    StepperMotor  *m_StepperMotor;

};

#endif

