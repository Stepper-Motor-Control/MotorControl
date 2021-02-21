
/*
 * Task.cpp
 *
 *  Created on: Oct 13, 2020
 *      Author: dinesh
 */

#include "Task.h"

int32_t Task::Init(void)
{
    pthread_attr_init(&m_attr);
    pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&m_threads, &m_attr, Task::ProcessData, static_cast<void *>(this));
    return 0;
}

int32_t Task::Process(void *pContext)
{
    cout << "This needs to be implimented" << endl;
    return 0;
}

void *Task::ProcessData(void *pContext)
{
    Task *pTask = reinterpret_cast <Task *>(pContext);
    {
        pTask->Process(pTask);
    }
    pthread_exit (NULL);
    return NULL;
}

int32_t Task::Wait(void)
{
    pthread_join(m_threads, NULL);
    return 1;
}


Task::Task() : m_Status(true)
{
  pthread_mutex_init(&m_lock, NULL);
}

Task::~Task()
{
    pthread_mutex_destroy(&m_lock);
    pthread_attr_destroy(&m_attr);
}


