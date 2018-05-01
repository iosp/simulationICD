#ifndef INTERNALGPSMESSAGE_H
#define INTERNALGPSMESSAGE_H

/*
* InternalGPSMessage.h
* INS internal GPS message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InsMessage.h"

class InternalGPSMessage : public InsMessage {
protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const override;

	virtual int GetMessageSize() const override;
		
public:

	InternalGPSMessage(float hertz);

	virtual ~InternalGPSMessage() = default;

	virtual void FillMessage(const InsData& data) override;

	virtual std::bitset<8> GetMsgBitID() const override;
};

#endif // INTERNALGPSMESSAGE_H