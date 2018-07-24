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

static const int DATA_LEN = 8;
static const int COMMAND_LEN = 3;

class IdanMessageSend : public IdanMessage {
public:
	IdanMessageSend() = default;
	
	virtual ~IdanMessageSend() = default;

	// Fill the message buffer with a message, ID and length
	template <class MSG>
	void FillBuffer(MSG msg) {
		t_msgID id = GetMsgID();
		// canview interface
		if (m_isCanView) {
			int msgLen = DATA_LEN + COMMAND_LEN + 2;
			m_buffer[0] = 'C';
			m_buffer[1] = msgLen - 2;
			m_buffer[2] = 0; // CAN_VIEW_SEND_11_BIT
			m_buffer[3] = (unsigned char)((id & 0xff00) >> 8);
			m_buffer[4] = (unsigned char)(id & 0x00ff);
			memcpy(&m_buffer[5], &msg, DATA_LEN);
			int crc = 0;
			for (int i = 0; i < msgLen; i++) {
				crc = crc ^ m_buffer[i];
			}
			m_buffer[msgLen] = crc;
			m_buffer[msgLen + 1] = '\r';
		}
		// can (linux) interface
		else {
			memcpy(m_buffer, &id, sizeof(t_msgID));
			memcpy(m_buffer + 4, &DATA_LEN, sizeof(int));
			memcpy(m_buffer + 8, &msg, sizeof(msg));
		}

	}
};

#endif // IDANMESSAGESEND_H