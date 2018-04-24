#ifndef ECHOMESSAGE_H
#define ECHOMESSAGE_H

/*
* EchoMessage.h
* INS echo message to send
* Author: Binyamin Appelbaum
* Date: 27.02.18
*/

#include "InsMessage.h"

class EchoMessage : public InsMessage {
protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:

	EchoMessage(float hertz);

	virtual ~EchoMessage() = default;

	virtual void FillMessage(const InsData& data) override;

};

#endif // ECHOMESSAGE_H