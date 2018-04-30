#ifndef IDANMESSAGE_H
#define IDANMESSAGE_H

/*
* IdanMessage.h
* IDAN message
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "IMessage.h"
#include <stdint.h> // uins32_t
#include <map>

typedef uint32_t t_msgID;
static const t_msgID HLC_PRIM_ID = 0x50;
static const t_msgID HLC_SEC_ID = 0x70;
static const t_msgID IDAN_PRIM_ID = 0x60;
static const t_msgID IDAN_SEC_REP_ID = 0x80;
static const t_msgID IDAN_SEC_SEN_ID = 0x81;

class IdanData;

class IdanMessage : public IMessage<IdanData>{
public:
	IdanMessage(float hertz);

	virtual ~IdanMessage() = default;

	virtual t_msgID GetMsgID() const = 0;

};

#endif // IDANMESSAGE_H