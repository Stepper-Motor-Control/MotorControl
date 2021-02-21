
#ifndef  CLIENT_COMMS_TCP_H
#define  CLIENT_COMMS_TCP_H

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

class Client
{
public:

   Client() ;
   Client(int32_t port) ;

   int32_t init(char *pIpAddress = NULL );
   int32_t SendData(char *pData, int32_t dataSize);
   int32_t ReadData(char *pDataReceive, int32_t dataSize);
   int32_t ReadData(char *pDataReceive);

   virtual ~Client();

private:
   int32_t m_Port;
   int32_t m_Socket;
   struct sockaddr_in m_ServAddr;
   static const int32_t MAX_RECEIVE_BUFFER = 1024 * 10;
   static const int32_t MAX_IP_ADDRESS = 100;
   char m_IpAddress[MAX_IP_ADDRESS];
   char m_RecBuffer[MAX_RECEIVE_BUFFER];
};

#endif
