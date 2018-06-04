#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H

/*
* StatusMessage.h
* Tiltan status message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "TiltanMessage.h"

class StatusMessage : public TiltanMessage {
protected:	
	virtual void FillHeader(/* out */TILTAN_HEADER& header) const override;

	virtual int GetMessageSize() const override;
		
public:

	StatusMessage() = default;

	virtual ~StatusMessage() = default;

	virtual void FillMessage(const TiltanData& data) override;

	virtual TiltanMsgType GetMsgType() const override;
};

#endif // STATUSMESSAGE_H