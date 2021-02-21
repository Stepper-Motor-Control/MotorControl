/*
 * Comms.cpp
 *
 *  Created on: Oct 9, 2020
 *      Author: dinesh
 */

#include "Comms.h"
#include <string.h>

int32_t Comms::Init(int32_t portNo)
{
   m_PortNo = portNo;
   //create a master socket
   if ((m_MasterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
   {
      perror("socket failed");
      exit(EXIT_FAILURE);
   }

   //set master socket to allow multiple connections ,
   //this is just a good habit, it will work without this
   int32_t opt = TRUE;
   if (setsockopt(m_MasterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                  sizeof(opt)) < 0)
   {
      perror("setsockopt");
      exit(EXIT_FAILURE);
   }

   // SO_SNDBUF
   //     Sets send buffer size. This option takes an int value.
   int optSndBuffer  = MAX_RECEIVE_BUFFER;
   if (setsockopt(m_MasterSocket, SOL_SOCKET, SO_SNDBUF, &optSndBuffer, sizeof(optSndBuffer)) < 0)
   {
      perror("ERROR Setting Send buffer");
      exit(EXIT_FAILURE);
   }

   // SO_RCVBUF
   //     Sets receive buffer size. This option takes an int value.
   int optReceiveBuffer  = MAX_RECEIVE_BUFFER;
   if (setsockopt(m_MasterSocket, SOL_SOCKET, SO_RCVBUF, &optReceiveBuffer, sizeof(optReceiveBuffer)) < 0)
   {
      perror("ERROR Setting Receive buffer");
      exit(EXIT_FAILURE);
   }

   //type of socket created
   m_Address.sin_family = AF_INET;
   m_Address.sin_addr.s_addr = INADDR_ANY;
   m_Address.sin_port = htons(m_PortNo);

   //bind the socket to localhost port 8888
   if (bind(m_MasterSocket, (struct sockaddr *)&m_Address, sizeof(m_Address)) < 0)
   {
      perror("bind failed");
      exit(EXIT_FAILURE);
   }
   printf("Listener on port %d \n", m_PortNo);

   //try to specify maximum of 3 pending connections for the master socket
   if (listen(m_MasterSocket, 3) < 0)
   {
      perror("listen");
      exit(EXIT_FAILURE);
   }

   //accept the incoming connection
   m_AddrLen = sizeof(m_Address);
   puts("Waiting for connections ...");

   Task::Init();

   if (!IsInitializationDone())
   {
      sleep(1);
   }

   printf("Done %s : %d",__FUNCTION__,__LINE__);

   
   return 0;
}

int32_t Comms::SetupClient(void)
{

   //clear the socket set
   FD_ZERO(&m_ReadFds);

   //add master socket to set
   FD_SET(m_MasterSocket, &m_ReadFds);
   m_MaxSd = m_MasterSocket;

   //add child sockets to set
   for (int32_t i = 0; i < MAX_CLIENTS; i++)
   {
      //socket descriptor
      m_Sd = m_ClientSocket[i];

      //if valid socket descriptor then add to read list
      if (m_Sd > 0)
      {
         FD_SET(m_Sd, &m_ReadFds);
      }

      //highest file descriptor number, need it for the select function
      if (m_Sd > m_MaxSd)
      {
         m_MaxSd = m_Sd;
      }
   }

   return 0;

}

int32_t  Comms::IsThereNewConnection(void)
{
   int32_t new_socket  = 0;
   //If something happened on the master socket ,
   //then its an incoming connection
   if (FD_ISSET(m_MasterSocket, &m_ReadFds))
   {
      if ((new_socket = accept(m_MasterSocket, (struct sockaddr *)&m_Address, (socklen_t *)&m_AddrLen)) < 0)
      {
         perror("accept");
         exit(EXIT_FAILURE);
      }

      //inform user of socket number - used in send and receive commands
      printf("New connection , socket fd is %d , ip is : %s , port : %d \n", new_socket,
             inet_ntoa(m_Address.sin_addr), ntohs
             (m_Address.sin_port));

      //a message
      const char *message = "ECHO Daemon v1.0 \r\n";

      //send new connection greeting message
      if (send(new_socket, message, strlen(message), 0) != strlen(message))
      {
         perror("send");
      }

      puts("Welcome message sent successfully");

      //add new socket to array of sockets
      for (int i = 0; i < MAX_CLIENTS; i++)
      {
         //if position is empty
         if (m_ClientSocket[i] == 0)
         {
            m_ClientSocket[i] = new_socket;
            printf("Adding to list of sockets as %d\n", i);
            break;
         }
      }
   }


   return 0;
}

int32_t  Comms::GetData(void)
{
   int32_t sd  = 0;
   int32_t addrlen = 0;
   int32_t readSize = 0;
   struct sockaddr_in address;

   for (int i = 0; i < MAX_CLIENTS; i++)
   {
      sd = m_ClientSocket[i];
      //If something happened on the master socket ,
      //then its an incoming connection
      if (FD_ISSET(sd, &m_ReadFds))
      {

         //Check if it was for closing , and also read the
         //incoming message
         memset(m_RecBuffer, 0, sizeof(m_RecBuffer));
         if ((readSize = read(sd, m_RecBuffer, sizeof(m_RecBuffer))) == 0)
         {
            //Somebody disconnected , get his details and print
            getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
            printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr),
                   ntohs(address.sin_port));

            //Close the socket and mark as 0 in list for reuse
            close(sd);
            m_ClientSocket[i] = 0;
         }

         //Echo back the message that came in
         else
         {
             //set the string terminating NULL byte on the end  
             //of the data read  
             //m_RecBuffer[readSize] = '\0';  
             //printf("Dinesh Received Data Socket %d %s\n" , sd, m_RecBuffer);   
             //send(sd, m_RecBuffer, readSize, 0);
             ReceivedData(sd,m_RecBuffer,readSize);
         }

      }

   }

   return 0;
}

int32_t  Comms::Process(void *pContext)
{
   Comms *pComms = reinterpret_cast<Comms *>(pContext);

   int32_t activity = 0;
   while (pComms->GetStatus())
   {
      SetupClient();
      DoneInitialization();
      //wait for an activity on one of the sockets , timeout is NULL ,
      //so wait indefinitely
      activity = select(m_MaxSd + 1, &m_ReadFds, NULL, NULL, NULL);

      if ((activity < 0) && (errno != EINTR))
      {
         printf("select error");
      }

      IsThereNewConnection();
      GetData();
   }
   return 0;
}


Comms::Comms() : m_MasterSocket(0), m_AddrLen(0), m_NewSocket(0),
   m_PortNo(0), m_Sd(0), m_Status(true), m_DoneInitialization(false)
{
   FD_ZERO(&m_ReadFds);
   memset(m_ClientSocket, 0, sizeof(m_ClientSocket));
   memset(&m_Address, 0, sizeof(m_Address));
   memset(m_RecBuffer, 0, sizeof(m_RecBuffer));
}

Comms::~Comms()
{

}




