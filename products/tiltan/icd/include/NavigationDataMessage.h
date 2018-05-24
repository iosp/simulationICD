#ifndef NAVIGATIONDATAMESSAGE_H
#define NAVIGATIONDATAMESSAGE_H

/*
* NavigationDataMessage.h
* Tiltan navigation data message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "TiltanMessage.h"

class NavigationDataMessage : public TiltanMessage {
protected:

	virtual void FillHeader(/* out */ TILTAN_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:

	NavigationDataMessage() = default;
	
	virtual ~NavigationDataMessage() = default;

	virtual void FillMessage(const TiltanData& data) override;

	virtual TiltanMsgType GetMsgType() const override;	
};

#endif // NAVIGATIONDATAMESSAGE_H