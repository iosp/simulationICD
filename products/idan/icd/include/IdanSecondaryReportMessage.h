#ifndef IDAN_SECONDARY_REPORT_MSG_H
#define IDAN_SECONDARY_REPORT_MSG_H

/*
* IdanSecondaryReportMessage.h
* Idan secondary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "IdanMessageSend.h"
#include "IdanStructs.h"

class IdanSecondaryReportMessage : public IdanMessageSend {
public:
	IdanSecondaryReportMessage() = default;

	virtual ~IdanSecondaryReportMessage() = default;
	
	virtual int GetMessageSize() const override;

	virtual void FillMessage(const IdanData& data) override;

	virtual t_msgID GetMsgID() const override;
};

#endif // IDAN_SECONDARY_REPORT_MSG_H