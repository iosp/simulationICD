#ifndef PERIODIC_100HZ_H
#define PERIODIC_100HZ_H

/*
* Periodic100HZMessage.h
* Periodic 1 hz message to send
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "IponMessage.h"

class Periodic100HZMessage : public IponMessage {
public:
	Periodic100HZMessage() = default;

	virtual ~Periodic100HZMessage() = default;

	virtual void FillMessage(const IponData& data) override;

	virtual int GetMessageSize() const override;

	virtual IponMsgType GetMsgType() const override;
};

#endif // PERIODIC_100HZ_H