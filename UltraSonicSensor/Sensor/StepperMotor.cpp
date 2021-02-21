/**********************************************************************
 * Description
 * 
**********************************************************************/
#include <wiringPi.h>
#include <sys/time.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include "MessageData.h"
#include "StepperMotor.h"

void *StepperMotor::ProcessData(void *pContext)
{
    StepperMotor *pTask = reinterpret_cast <StepperMotor *>(pContext);
    int32_t bytes_read     = 0;
    mqd_t  localMshHandler = pTask->GetMsgQueueHandler();
    char   *lBuffer        = pTask->GetBuffer();
    int32_t lsize          = pTask->GetSizeofBuffer(); 
    uint32_t lsender        = 0; 
    MessageData            nextMessage ;
    int32_t                qsize = 0;
    stringstream debugOutput(ios::in|ios::out);

    // Detach the thread
    pthread_detach (pthread_self());

    while ( pTask->GetStatus())
    {
        if (pTask->m_StepperQueue.empty())
        {
            usleep(10000); // sleep 0.01 sec before trying again
            continue;
        }
        // we end up here because there was something in the msg queue
        pTask->Lock(); 
        qsize =  pTask->m_StepperQueue.size();

        if(qsize > 5)
        {
            cout << "Queue size: " << qsize << endl;
        }
        nextMessage = pTask->m_StepperQueue.front(); // get next message in queue
        pTask->m_StepperQueue.pop();             // remove it from the queue
        pTask->UnLock(); 

        cout << "Processing value " << nextMessage.getMsgDst() << endl;

        usleep(2000000);

    }
    pthread_exit (NULL);
    return NULL;
}


  int32_t StepperMotor::ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize)
   {
       std::cout << "This function needs to be implimented" << std::endl;
       return 0;
   }

 int32_t StepperMotor::SendStepperpos(MessageData &data)
   {
       Lock(); 
       m_StepperQueue.push(data);
       UnLock
       return 0;
   }



int32_t StepperMotor::Wait(void)
{
    Comms::Wait();
    pthread_join(m_threads, NULL);
    return 1;
}

StepperMotor::StepperMotor(void) : m_debug(true) , m_Status(true), m_BytesRead(0)
{
   printf("Starting comms interface %s::Init...\n",__FUNCTION__,__LINE__);
   pthread_mutex_init(&m_lock, NULL);
   pthread_attr_init(&m_attr);
   pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);
   pthread_create(&m_threads, &m_attr, StepperMotor::ProcessData, static_cast<void *>(this));
   memset(m_WriteBuffer,0,sizeof(m_WriteBuffer));

   // unlink the queue if it exisits - debug
   mq_unlink (MAIN_QNAME);
   memset(&m_MsgqAttr,0,sizeof(m_MsgqAttr));

   printf ("Func:%s, Line:%d\n",__FUNCTION__,__LINE__); 

   Comms::Init(PORT_TO_CONNECT);

}

StepperMotor::~StepperMotor(void)
{
   pthread_mutex_destroy(&m_lock);
   pthread_attr_destroy(&m_attr);
}



