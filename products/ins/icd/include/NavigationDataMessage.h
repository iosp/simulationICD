#ifndef NAVIGATIONDATAMESSAGE_H
#define NAVIGATIONDATAMESSAGE_H

/*
* NavigationDataMessage.h
* INS navigation data message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InsMessage.h"

class NavigationDataMessage : public InsMessage {
protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:

	NavigationDataMessage(float hertz);
	
	virtual ~NavigationDataMessage() = default;

	virtual void FillMessage(const InsData& data) override;

	virtual std::bitset<8> GetMsgBitID() const override;
	
};

#endif // NAVIGATIONDATAMESSAGE_H