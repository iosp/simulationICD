#ifndef IDANMESSAGESEND_H
#define IDANMESSAGESEND_H

/*
* IdanMessageSend.h
* IDAN message to send
* Author: Binyamin Appelbaum
* Date: 29.03.18
*/

#include "IdanMessage.h"
#include <string.h> // memcpy

class IdanMessageSend : public IdanMessage {
public:
	IdanMessageSend(int hertz);

	virtual ~IdanMessageSend() = default;

	virtual int SendMessage(ICommunication* comm) const override;

	// Fill the message buffer with a message, ID and length
	template <class MSG>
	void FillBuffer(MSG msg) {
		t_msgID id = GetMsgID();
		int length = 8;
		memcpy(m_buffer, &id, sizeof(t_msgID));
		memcpy(m_buffer + 4, &length, sizeof(int));
		memcpy(m_buffer + 8, &msg, sizeof(msg));
	}
};

#endif // IDANMESSAGESEND_H