/**********************************************************************
* Filename    : Sweep.c
* Description : Servo sweep
* Author      : www.freenove.com
* modification: 2019/12/27
**********************************************************************/
#include "PositionServoMotor.h"

PositionServoMotor& PositionServoMotor::GetInstance(void)
{
   static PositionServoMotor refPositionServoMotor;

   return refPositionServoMotor;
}

int32_t PositionServoMotor::Init(int32_t pin)
{

   if (m_debug)
   {
      cout << "Function : " << __FUNCTION__  << " Line : " << __LINE__ << "  Pin: " <<  pin << endl;
   }

   int32_t retVal = softPwmCreate(pin, 0, 200);

   return retVal;
}

void PositionServoMotor::RotateAtAngel(int pin, int angle)
{
   if (angle > 180)
   {
      angle = 180;
   }
   if (angle < 0)
   {
      angle = 0;
   }

   if (m_debug)
   {
      cout << "Function : " << __FUNCTION__  << " Line : " << __LINE__ << "  Pin: " <<  pin << "  Angle: " <<  angle << endl;
   }

   softPwmWrite(pin, map(angle, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS));
}

void PositionServoMotor::PulseMS(int pin, int ms)
{
   if (ms > SERVO_MAX_MS)
   {
      ms = SERVO_MAX_MS;
   }
   if (ms < SERVO_MIN_MS)
   {
      ms = SERVO_MIN_MS;
   }


   if (m_debug)
   {
      cout << "Function : " << __FUNCTION__  << " Line : " << __LINE__ << "  Pin: " <<  pin << "  Pulse_ms: " <<  ms << endl;
   }

   softPwmWrite(pin, ms);
}

int32_t PositionServoMotor::map(uint32_t value,
                                uint32_t fromLow,
                                uint32_t fromHigh,
                                uint32_t toLow,
                                uint32_t toHigh)
{
   if (value == 0)
   {
      return -1;
   }
   char m_buffer[256];
   memset(m_buffer, 0, sizeof(m_buffer));
   double val0 = double((double(toHigh - toLow))*(double(value - fromLow)));
   double val1 = (double(fromHigh - fromLow))+(double(toLow));
   double ans = val0 / val1;
   snprintf(m_buffer, sizeof(m_buffer), " val0= %f,val1 = %f,ans = %f ",  val0, val1, ans);

   if (m_debug)
   {
      cout << __FUNCTION__ << " " << __LINE__ << " " << m_buffer << endl;
   }
   return int32_t(ans);
}

int32_t PositionServoMotor::PositionControl(void)
{
   int i;

   printf("Program is starting ...\n");

   wiringPiSetup();
   Init(1); //initialize PMW pin of servo
   while (1)
   {
      for (i = SERVO_MIN_MS; i < SERVO_MAX_MS; i++)
      { //make servo rotate from minimum angle to maximum angle
         PulseMS(1, i);
         delay(10);
      }
      delay(500);
      for (i = SERVO_MAX_MS; i > SERVO_MIN_MS; i--)
      { //make servo rotate from maximum angle to minimum angle
         PulseMS(1, i);
         delay(10);
      }
      delay(500);
   }
   return 0;
}

int32_t PositionServoMotor::PositionControlAngle(void)
{
   int i;

   printf("Program is starting ...\n");

   wiringPiSetup();
   Init(1); //initialize PMW pin of servo
   while (1)
   {
      for (i = 5; i < 180; i += 5)
      { //make servo rotate from minimum angle to maximum angle
         RotateAtAngel(1, i);
         delay(10);
      }
      delay(500);
/*        
        for (i = 180; i > SERVO_MIN_MS; i-= 5)
        { //make servo rotate from maximum angle to minimum angle
            RotateAtAngel(1, i);
            delay(10);
        }
        delay(500);
  */
   }
   return 0;
}

int32_t PositionServoMotor::Init(void)
{
   int i;
   printf("Starting comms interface PositionServoMotor::Init...\n");
   wiringPiSetup();
   Init(1);
   //Comms::Init();

   return 0;
}

int32_t PositionServoMotor::ReceivedData(int32_t sockdf, char *pDataTransmit, int32_t dataSize)
{
   ServoDataMessage::ServoDataMsg *pServoDataMsg = reinterpret_cast<ServoDataMessage::ServoDataMsg *>(pDataTransmit);
   int32_t angle = pServoDataMsg->v.m_IPos;
   //RotateAtAngel(1, angle);
   PulseMS(1, angle);
   return 0;
}



PositionServoMotor::PositionServoMotor(void) : m_debug(true)
{
    Init();
}

PositionServoMotor::~PositionServoMotor(void)
{

}

