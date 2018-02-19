#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H

/*
* StatusMessage.h
* INS status message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InsMessage.h"

class StatusMessage : public InsMessage {
protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:
	StatusMessage(int hertz);
	virtual ~StatusMessage() = default;

	virtual void FillMessage(const InsData& data) override;

};

#endif // STATUSMESSAGE_H