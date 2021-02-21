/*
 * Comms.h
 *
 *  Created on: Oct 9, 2020
 *      Author: dinesh
 */

#ifndef COMMS_H_
#define COMMS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <cstdio>
#include <cinttypes>

#include "MessageData.h"
#include "Task.h"
using namespace std;

#ifndef   TRUE    
#define TRUE   1
#endif

#ifndef  FALSE
#define FALSE  0
#endif

class Comms   :public Task
{
public:
   Comms();
   virtual ~Comms();
   int32_t Init(int32_t portNo = 8888);

   bool GetStatus(void)
   {
       return m_Status;
   }
   
   void SetStatus(bool status)
   {
       m_Status = status;
   }

   virtual int32_t ReceivedData(int32_t sockdf , char *pDataTransmit , int32_t dataSize)
   {
       std::cout << "This function needs to be implimented" << std::endl;
       return 0;
   }


    int32_t WriteData(int32_t sockdf , char *pDataTransmit , int32_t dataSize)
    {
        int32_t noBytesSent = 0;
        noBytesSent = write(sockdf, pDataTransmit, dataSize);
        if (noBytesSent < 0)
        {
            error("ERROR writing to socket");
        }

        return 0;
    }

    int32_t ReadData(int32_t sockdf , char *pDataReceive , int32_t dataSize)
    {
        int32_t noBytesReceive = 0;

        noBytesReceive = read(sockdf, pDataReceive, dataSize);

        if (noBytesReceive < 0)
        {
            error("ERROR read to socket");
        }

        /// Read message header and
        return noBytesReceive;
    }

    bool IsInitializationDone(void) { return m_DoneInitialization;}
    void DoneInitialization(void) { m_DoneInitialization = true;}



private:

   /**
    * Local variables
    */
   int32_t m_MasterSocket;
   int32_t m_AddrLen;
   int32_t m_NewSocket;
   static const int32_t MAX_CLIENTS = 30;
   int32_t m_ClientSocket[MAX_CLIENTS];
   int32_t m_Sd;
   int32_t m_PortNo;
   int     m_MaxSd;
   struct sockaddr_in m_Address;

   static const int32_t MAX_RECEIVE_BUFFER = 1024 * 10;

   char m_RecBuffer[MAX_RECEIVE_BUFFER];

   //set of socket descriptors
   fd_set m_ReadFds;

   bool m_Status;

   /**
    * Setup threads
    */
   int32_t  Process(void *pContext);

   int32_t  SetupClient(void);

   int32_t  IsThereNewConnection(void);

   int32_t  GetData(void);

   void error(const char *msg)
    {
        perror(msg);
        exit(0);
    }

    bool m_DoneInitialization;

   Comms(const Comms& other) { }
   Comms(Comms&& other) { }
};

#endif /* COMMS_H_ */


