#ifndef STATUSMESSAGE_H
#define STATUSMESSAGE_H

/*
* StatusMessage.h
* INS status message to send
* Author: Binyamin Appelbaum
* Date: 14.02.18
*/

#include "InsMessage.h"

class EchoMessage;

class StatusMessage : public InsMessage {
private:

	EchoMessage* m_echoMessage;

protected:

	virtual void FillHeader(/* out */ INS_HEADER& header) const override;

	virtual int GetMessageSize() const override;
	
public:

	StatusMessage(int hertz);

	virtual ~StatusMessage();

	virtual void FillMessage(const InsData& data) override;

	virtual void SendMessage(ICommunication* comm) const override;

};

#endif // STATUSMESSAGE_H