#ifndef INTERNALGPSMESSAGE_H
#define INTERNALGPSMESSAGE_H

/*
* InternalGPSMessage.h
* Tiltan internal GPS message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "TiltanMessage.h"

class InternalGPSMessage : public TiltanMessage {
protected:

	virtual void FillHeader(/* out */ TILTAN_HEADER& header) const override;

	virtual int GetMessageSize() const override;
		
public:

	InternalGPSMessage() = default;

	virtual ~InternalGPSMessage() = default;

	virtual void FillMessage(const TiltanData& data) override;

	virtual TiltanMsgType GetMsgType() const override;
};

#endif // INTERNALGPSMESSAGE_H