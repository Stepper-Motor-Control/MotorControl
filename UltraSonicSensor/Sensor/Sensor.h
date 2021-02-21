/**********************************************************************
* Description : Get distance via UltrasonicRanging sensor
**********************************************************************/


#ifndef INFRARED_SENSOR_H_
#define INFRARED_SENSOR_H_

#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include "Comms.h"

using namespace std;



class Sensor : public Comms
{
public:
    //Sensor(void) ;
    ~Sensor(void);
    static Sensor & GetInstance (void);
    int32_t Wait(void);
    
   double getSonar(void);

   bool GetStatus(void)
   {
       return m_Status;
   }

   void SetStatus(bool status)
   {
       m_Status = status;
   }

   double GetDistance(void)
   {
       return m_DistanceInterface;
   }

   void SetCalculatedDistance(double distance)
   {
       if (m_IndexStoreDistance > MAX_STORAGE ) 
       {
           m_IndexStoreDistance = 0;
       }
    m_StoreDistance[m_IndexStoreDistance++] = distance;
    m_DistanceInterface = distance; 

   }
private:
    Sensor(void) ;
    uint32_t m_debug;
    bool m_Status;
    
    // If the module does not return high level, we cannot wait for this forever, 
    // so we need to calculate the time period for the maximum distance, that is, 
    // time Out. timeOut= 2*MAX_DISTANCE/100/340*1000000. The result of the 
    // constant part in this formula is approximately 58.8. 
    static const int32_t TRIGGER_PIN     = 4;
    static const int32_t ECHO_PIN        = 5;
    static const int32_t MAX_DISTANCE    = 220;
    static const int32_t MAX_TIME_OUT    = MAX_DISTANCE *60;  

    double m_MaxTimeOut ;

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
    int32_t pulseIn(int32_t pin, int32_t level, int32_t timeout);
    int32_t getElapsedTime(int32_t pin, int32_t level, int32_t timeout,
                                   struct timeval *endTime , struct timeval *startTime);

    int32_t ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize);

    static const int32_t PORT_TO_CONNECT = 8889;
    static const int32_t MAX_STORAGE     = 100;

    double m_StoreDistance[MAX_STORAGE];
    int32_t m_IndexStoreDistance;
    double m_DistanceInterface;

                                  
    

};

#endif