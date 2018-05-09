#ifndef PERIODIC_1HZ_H
#define PERIODIC_1HZ_H

/*
* Periodic1HZMessage.h
* Periodic 1 hz message to send
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "IponMessage.h"

class Periodic1HZMessage : public IponMessage {
public:
	Periodic1HZMessage(float hertz);

	virtual ~Periodic1HZMessage() = default;

	virtual void FillMessage(const IponData& data) override;

	virtual int GetMessageSize() const override;
};

#endif // PERIODIC_1HZ_H