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
	
public:
	StatusMessage();
	virtual ~StatusMessage() = default;

	virtual void FillMessage(const InsData& data) override;
};

#endif // STATUSMESSAGE_H