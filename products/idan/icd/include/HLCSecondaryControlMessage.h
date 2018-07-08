#ifndef HLC_SECONDARY_CTRL_MSG_H
#define HLC_SECONDARY_CTRL_MSG_H

/*
* HLCSecondaryControlMessage.h
* HLC secondary message to send
* Author: Binyamin Appelbaum
* Date: 26.03.18
*/

#include "IdanMessageGet.h"
#include "IdanStructs.h"

class HLCSecondaryControlMessage : public IdanMessageGet {
private:
	HLC_SecondaryControlMsgType m_message;
	
public:
	HLCSecondaryControlMessage(float hertz, bool m_isCanView);

	virtual ~HLCSecondaryControlMessage() = default;

	virtual void ParseMessage(const char* buffer) override;

	virtual void UpdateData(IdanData& data) const override;

	virtual t_msgID GetMsgID() const override;
};

#endif // HLC_SECONDARY_CTRL_MSG_H