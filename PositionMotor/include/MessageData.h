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
    struct MsgHdr
    {
        uint32_t msgStart ;
        uint32_t msgSize ;
        uint32_t msgId ;
        uint32_t msgSrc;
        uint32_t msgDst;
        uint32_t msgCrc;
    };
private:
    MessageData();
    virtual ~MessageData();

};

#endif /* MESSAGEDATA_H_ */


