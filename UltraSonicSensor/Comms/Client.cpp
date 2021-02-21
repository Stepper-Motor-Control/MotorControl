/*
 * Client.cpp
 *
 *  Created on: Oct 9, 2020
 *      Author: dinesh
 */

#include "Client.h"
#include <string.h>


Client::Client()  : m_Port(0), m_Socket(0)
{
   memset(&m_ServAddr, 0, sizeof(struct sockaddr_in));
   memset(m_IpAddress, 0, sizeof(m_IpAddress));
}

Client::Client(int32_t port) : m_Port(port), m_Socket(0)
{
   memset(&m_ServAddr, 0, sizeof(struct sockaddr_in));
   memset(m_IpAddress, 0, sizeof(m_IpAddress));
}

  int32_t Client::init(char *pIpAddress)
   {
      int32_t retStatus = 0;
      char *ip="127.0.0.1";

      if (pIpAddress == NULL)
      {
          strncpy(m_IpAddress, "127.0.0.1", sizeof(m_IpAddress));
      }
      else
      {
          strncpy(m_IpAddress, pIpAddress, sizeof(m_IpAddress));
      }
            
      if ((m_Socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
         printf("\n Socket creation error \n");
         retStatus = -1;
      }

      if (retStatus == 0 )
      {
          m_ServAddr.sin_family        = AF_INET;
          m_ServAddr.sin_addr.s_addr   = htonl(*ip);
          m_ServAddr.sin_port          = htons(m_Port);
      
          if (connect(m_Socket, (struct sockaddr *)&m_ServAddr, sizeof(m_ServAddr)) < 0)
          {
             printf("\nConnection Failed \n");
             retStatus = -1;
          }
      }

      return retStatus;
   }

  int32_t Client::SendData(char *pData, int32_t dataSize)
   {
      int32_t retStatus = 0;

      memset(m_RecBuffer, 0, sizeof(m_RecBuffer));

      if ((retStatus = write(m_Port, pData, dataSize)) < 0)
      {
         printf("Func:%s Line:%d Failed :%d\n", __FUNCTION__, __LINE__, retStatus);
      }
      return retStatus;
   }

   int32_t Client::ReadData(char *pDataReceive, int32_t dataSize)
   {
      int32_t noBytesReceive = 0;

      noBytesReceive = read(m_Socket, pDataReceive, dataSize);

      if (noBytesReceive < 0)
      {
         printf("Func:%s Line:%d Failed :%d\n", __FUNCTION__, __LINE__, noBytesReceive);
      }

      return noBytesReceive;
   }

   int32_t Client::ReadData(char *pDataReceive)
   {
      int32_t noBytesReceive = 0;
      int32_t maxBytesReceive = sizeof(m_RecBuffer);
      pDataReceive = static_cast<char *>(m_RecBuffer);

      noBytesReceive = read(m_Socket, m_RecBuffer, maxBytesReceive);

      if (noBytesReceive <= 0)
      {
         printf("Func:%s Line:%d Failed :%d\n", __FUNCTION__, __LINE__, noBytesReceive);
      }

      return noBytesReceive;
   }




Client::~Client()
{

}




   