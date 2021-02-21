/*
 * Task.h
 *
 *  Created on: Oct 13, 2020
 *      Author: dinesh
 */

#ifndef TASK_H_
#define TASK_H_

#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Task
{
public:
   Task();
   virtual ~Task();

   int32_t          Init(void);
   int32_t          Wait(void);
   virtual int32_t  Process(void *pContext);

   void             Lock(void) 
   {
       pthread_mutex_lock(&m_lock);
   }


   void             UnLock(void) 
   {
       pthread_mutex_unlock(&m_lock);
   }

   bool GetStatus(void)
   {
       return m_Status;
   }

   void SetStatus(bool status)
   {
       m_Status = status;
   }



private:

    pthread_mutex_t m_lock;
    pthread_attr_t  m_attr;
    pthread_t       m_threads;
    bool            m_Status;
    static void *ProcessData(void *pContext);

};

#endif /* TASK_H_ */

