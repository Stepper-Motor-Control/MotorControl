/*
 * ServoDataMessage.h
 *
 *  Created on: Oct 9, 2020
 *      Author: dinesh
 */

#ifndef SERVODATAMESSAGE_H_
#define SERVODATAMESSAGE_H_

#include <iostream>
#include <cstdio>
#include <cinttypes>
#include "MessageData.h"

using namespace std;

class ServoDataMessage : MessageData
{
public:
   struct ServoDataMsg 
   {
      MsgHdr m_msg;
      union DataMsg 
      {
         int32_t    m_IPos;
         double     m_DPos;
      }v;

   };


private:
   ServoDataMessage();
   virtual ~ServoDataMessage();
};

#endif /* MESSAGEDATA_H_ */



