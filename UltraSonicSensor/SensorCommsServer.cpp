/**********************************************************************
 * Description
 * 
**********************************************************************/

#include "SensorCommsServer.h"


void *SensorCommsServer::ProcessData(void *pContext)
{
    char dispBuffer[15];
    SensorCommsServer *pTask = reinterpret_cast <SensorCommsServer *>(pContext);
   //cd  pTask->m_pClientCommsTcp->init();
    while ( pTask->GetStatus())
    {
      std::cout << "Func:"<< __FUNCTION__ << " Line:"<<__LINE__<< " Distance:" << pTask->GetDistance() << std::endl;
      memset(dispBuffer , 0,sizeof(dispBuffer)) ;
      snprintf(dispBuffer,sizeof(dispBuffer),"%lf",pTask->GetDistance() );
      pTask->DispData(dispBuffer, 0);
      sleep(2);
    }
    pthread_exit (NULL);
    return NULL;
}

void SensorCommsServer::DispData(const char *pData, int32_t line)
{
    m_pLcdDisplay->Display(pData,line);
}

SensorCommsServer::SensorCommsServer(Sensor & sensor) : m_refSensor(sensor), 
                                                        m_debug(true) , 
                                                        m_Status(true)
{
   printf("Starting comms interface %s::Init...\n",__FUNCTION__,__LINE__);

   m_pClientCommsTcp = new Client(PORT_TO_CONNECT);
   // m_pClientCommsTcp->init();
   m_pLcdDisplay     = new LcdDisplay();
   m_StepperMotor    = new StepperMotor();
   
   pthread_mutex_init(&m_lock, NULL);
   pthread_attr_init(&m_attr);
   pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);
   pthread_create(&m_threads, &m_attr, SensorCommsServer::ProcessData, static_cast<void *>(this));
}

 int32_t SensorCommsServer::Wait(void)
 {
     return pthread_join(m_threads, NULL);
 }

SensorCommsServer::~SensorCommsServer(void)
{
   delete m_pLcdDisplay;
   pthread_mutex_destroy(&m_lock);
   pthread_attr_destroy(&m_attr);
}



