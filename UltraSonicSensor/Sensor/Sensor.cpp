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
#include <wiringPi.h>
#include <sys/time.h>
#include "Sensor.h"

Sensor& Sensor::GetInstance(void)
{
   static Sensor staticReferenceSensor;
   return staticReferenceSensor;
}

void *Sensor::ProcessData(void *pContext)
{
    Sensor *pTask = reinterpret_cast <Sensor *>(pContext);

    while ( pTask->GetStatus())
    {
       //// Call the routine to get the distance 
       double lDistance = pTask->getSonar();
       //std::cout << "Distance:" << lDistance << std::endl;
       pTask->SetCalculatedDistance(lDistance);
       sleep(1);
    }
    pthread_exit (NULL);
    return NULL;
}

int32_t Sensor::getElapsedTime(int32_t pin, 
                               int32_t level, 
                               int32_t timeout, 
                               struct timeval *endTime , 
                               struct timeval *startTime)
{
   int32_t micros = 0;

   gettimeofday(startTime, NULL);
   
   while (digitalRead(pin) != level)
   {
      gettimeofday(endTime, NULL);

       micros = 0;

      if (endTime->tv_sec > startTime->tv_sec) 
      {
          micros = 1000000L; 
      }

      micros += (endTime->tv_usec - startTime->tv_usec);
      
      if (micros > timeout) 
      {
         // Error 
          micros = -1;
          break;
      }
   }
   return micros;
}

//get the measurement result of ultrasonic module with unit: cm
double Sensor::getSonar(void)
{   
    int32_t pingTime = 0;
    double distance  = 0.0;

    digitalWrite(TRIGGER_PIN,HIGH); //send 10us high level to trigPin 
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN,LOW);
    
    pingTime = pulseIn(ECHO_PIN,HIGH,MAX_TIME_OUT);   //read plus time of echoPin
    distance = (double) ((pingTime * 340.0 )/ 2.0) / 10000.0; //calculate distance with sound speed 340m/s
    
    return distance;
}


int32_t Sensor::pulseIn(int32_t pin, int32_t level, int32_t timeout)
{
 struct timeval tn, t0, t1;
   int32_t micros;
   gettimeofday(&t0, NULL);
   micros = 0;
   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   gettimeofday(&t1, NULL);
   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);
   return micros;
}


  int32_t Sensor::ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize)
   {
       std::cout << "This function needs to be implimented" << std::endl;
       return 0;
   }



int32_t Sensor::Wait(void)
{
    Comms::Wait();
    pthread_join(m_threads, NULL);
    return 1;
}

Sensor::Sensor(void) : m_debug(true) , m_Status(true), m_IndexStoreDistance(0), m_DistanceInterface(0)
{
   printf("Starting comms interface %s::Init...\n",__FUNCTION__,__LINE__);
   wiringPiSetup();

   memset (m_StoreDistance, 0, sizeof(m_StoreDistance));
   

   // If the module does not return high level, we cannot wait for this forever, 
    // so we need to calculate the time period for the maximum distance, that is, 
    // time Out. timeOut= 2*MAX_DISTANCE/100/340*1000000. The result of the 
    // constant part in this formula is approximately 58.8.  
   m_MaxTimeOut= ((2* MAX_DISTANCE)/100) /340*1000000;

   // Send 10 micro secs pulse 5v, 12 milli amps 
   pinMode(TRIGGER_PIN,OUTPUT);
   // Make this pin low to receive the echo 
   pinMode(ECHO_PIN,INPUT);

   pthread_mutex_init(&m_lock, NULL);
   pthread_attr_init(&m_attr);
   pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);
   pthread_create(&m_threads, &m_attr, Sensor::ProcessData, static_cast<void *>(this));

   Comms::Init(8889);
 //  Wait();

}

Sensor::~Sensor(void)
{
   pthread_mutex_destroy(&m_lock);
   pthread_attr_destroy(&m_attr);
}



