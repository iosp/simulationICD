#ifndef IDAN_SECONDARY_SENSOR_MSG_H
#define IDAN_SECONDARY_SENSOR_MSG_H

/*
* IdanSecondarySensorMessage.h
* Idan secondary sensor message to send
* Author: Binyamin Appelbaum
* Date: 29.03.18
*/

#include "IdanMessageSend.h"
#include "IdanStructs.h"

class IdanSecondarySensorMessage : public IdanMessageSend {
public:
	IdanSecondarySensorMessage(float hertz);

	virtual ~IdanSecondarySensorMessage() = default;
	
	virtual int GetMessageSize() const override;

	virtual void FillMessage(const IdanData& data) override;

	virtual t_msgID GetMsgID() const override;
};

#endif // IDAN_SECONDARY_SENSOR_MSG_H