#ifndef BESTVELMESSAGE_H
#define BESTVELMESSAGE_H

/*
* BestVelMessage.h
* BestVel message to send
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include "NovatelMessage.h"

class BestVelMessage : public NovatelMessage {
protected:

	E_MESSAGE_ID_INPUT_NOVATEL_DLV3 GetMessageID() const override;

public:
	BestVelMessage() = default;

	virtual ~BestVelMessage() = default;

	virtual void FillMessage(const NovatelData& data) override;

	virtual int GetMessageSize() const override;
};

#endif // BESTVELMESSAGE_H