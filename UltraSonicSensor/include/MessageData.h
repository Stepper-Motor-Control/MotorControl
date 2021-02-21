/*
 * MessageData.h
 *
 *  Created on: Oct 9, 2020
 *      Author: dinesh
 */

#ifndef MESSAGEDATA_H_
#define MESSAGEDATA_H_

#include <iostream>
#include <cstdio>
#include <cinttypes>

using namespace std;

class MessageData
{
public:
    MessageData() { }
    virtual ~MessageData() { }

    static const int32_t MSG_DATA_SIZE = 1024;

    struct MsgHdr
    {
        uint32_t msgStart ;
        uint32_t msgSize ;
        uint32_t msgId ;
        uint32_t msgSrc;
        uint32_t msgDst;
        uint32_t msgCrc;
        char     msgPayLoad[MSG_DATA_SIZE];
    };

     uint32_t getMsgStart(void) { return m_MsgHeader.msgStart;}
     void     setMsgStart(uint32_t start) { m_MsgHeader.msgStart = start;}

     uint32_t getMsgSize(void) { return m_MsgHeader.msgSize;}
     void     setMsgSize(uint32_t size) { m_MsgHeader.msgSize = size;}

     uint32_t getMsgId(void) { return m_MsgHeader.msgId;}
     void     setMsgId(uint32_t id) { m_MsgHeader.msgId = id;}

     uint32_t getMsgSrc(void) { return m_MsgHeader.msgSrc;}
     void     setMsgSrc(uint32_t src) { m_MsgHeader.msgSrc = src;}

     uint32_t getMsgDst(void) { return m_MsgHeader.msgDst;}
     void     setMsgDst(uint32_t dst) { m_MsgHeader.msgDst = dst;}

     uint32_t getMsgCrc(void) { return m_MsgHeader.msgSrc;}
     void     setMsgCrc(uint32_t crc) { m_MsgHeader.msgSrc = crc;}

     char     *getMsgPayLoad(void) { return m_MsgHeader.msgPayLoad;}

     int32_t   setMsgPayLoad(char *pData, int32_t size) 
    {     
        int32_t retStatus = -1;

        if ((size <= 0)                         || 
           (size > sizeof(m_MsgHeader.msgPayLoad)))
        {
            return retStatus;
        }
        memcpy(m_MsgHeader.msgPayLoad,pData,size);

        return size;

    }



private:

MsgHdr  m_MsgHeader;

};

#endif /* MESSAGEDATA_H_ */


