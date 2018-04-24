#ifndef IDAN_PRIMARY_MSG_H
#define IDAN_PRIMARY_MSG_H

/*
* IdanPrimaryMessage.h
* Idan primary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "IdanMessageSend.h"
#include "IdanStructs.h"

class IdanPrimaryMessage : public IdanMessageSend {
public:
	IdanPrimaryMessage(float hertz);

	virtual ~IdanPrimaryMessage() = default;

	virtual int GetMessageSize() const override;

	virtual void FillMessage(const IdanData& data) override;

	virtual t_msgID GetMsgID() const override;
};

#endif // IDAN_PRIMARY_MSG_H