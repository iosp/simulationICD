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
	
public:
	NavigationDataMessage();
	virtual ~NavigationDataMessage() = default;

	virtual void FillMessage(const InsData& data) override;
};

#endif // NAVIGATIONDATAMESSAGE_H