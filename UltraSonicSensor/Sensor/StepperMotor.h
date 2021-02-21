/**********************************************************************
* Description : Get distance via UltrasonicRanging sensor
**********************************************************************/


#ifndef STEPPER_MOTOR_SENSOR_H_
#define STEPPER_MOTOR_SENSOR_H_

#include <wiringPi.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <mqueue.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <queue>	// the message queue
#include "Comms.h"
#include "MessageData.h"

using namespace std;

class StepperMotor : public Comms
{
public:
    StepperMotor(void) ;
    ~StepperMotor(void);

   int32_t Wait(void);

   mqd_t GetMsgQueueHandler (void) { return m_QueueHandle;}

   char *GetBuffer(void) { return m_WriteBuffer;}

   int32_t GetSizeofBuffer (void) { return sizeof(m_WriteBuffer);}

   int32_t SendStepperpos(MessageData &data);

   #define MAIN_QNAME "/STEPPER_MOTOR"
   static const int32_t PORT_TO_CONNECT = 8891;
   static const int32_t BUFFER_SIZE     = 100;

    queue<MessageData> m_StepperQueue;
    pthread_mutex_t    m_Lock;
    
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

    // queue handlers
     mqd_t m_QueueHandle;

    static void *ProcessData(void *pContext);
    int32_t ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize);
  
    char    m_WriteBuffer[BUFFER_SIZE];
    int32_t m_BytesRead;

    struct mq_attr m_MsgqAttr;
 
};

#endif