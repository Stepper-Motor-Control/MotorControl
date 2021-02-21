/*
 * ServoDataMessage.h
 *
 *  Created on: Oct 9, 2020
 *      Author: dinesh
 */

#ifndef SENSOR_ULTRASONIC_DATAMESSAGE_H
#define SENSOR_ULTRASONIC_DATAMESSAGE_H

#include <iostream>
#include <cstdio>
#include <cinttypes>
#include "MessageData.h"

using namespace std;

class UltraSonicDataMessage : MessageData
{
public:
   struct UltraSonicDataMsg 
   {
      MsgHdr m_msg;
      
      union DataMsg 
      {
         int32_t    m_IPos;
         double     m_DPos;
      }v;

   };


private:
   UltraSonicDataMessage();
   virtual ~UltraSonicDataMessage();
};

#endif 



