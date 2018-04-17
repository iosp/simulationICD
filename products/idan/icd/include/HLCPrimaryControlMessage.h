#ifndef HLC_PRIMARY_CTRL_MSG_H
#define HLC_PRIMARY_CTRL_MSG_H

/*
* HLCPrimaryControlMessage.h
* HLC primary message to send
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "IdanMessageGet.h"
#include "IdanStructs.h"

class HLCPrimaryControlMessage : public IdanMessageGet {
private:
	HLC_PrimaryControlMsgType m_message;
	
public:
	HLCPrimaryControlMessage(int hertz);

	virtual ~HLCPrimaryControlMessage() = default;

	virtual void ParseMessage(const char* buffer) override;

	virtual void UpdateData(IdanData& data) const override;

	virtual t_msgID GetMsgID() const override;
};

#endif // HLC_PRIMARY_CTRL_MSG_H