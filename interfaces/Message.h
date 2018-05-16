#ifndef MESSAGE_H
#define MESSAGE_H

/*
* Message.h
* Message interface
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

#include <cstring> // memset
#include "../communications/include/ICommunication.h" // sendData

static const int BUFFER_SIZE = 1000;

template <class TData>
class Message {
protected:
	char m_buffer[BUFFER_SIZE]{0};

public:
	Message() {}

	virtual ~Message() = default;

	virtual int GetMessageSize() const = 0;

	virtual void FillMessage(const TData& data) = 0;

	virtual void InitMessage() {
		memset(m_buffer, 0, BUFFER_SIZE);
	}

	virtual int SendMessage(ICommunication* comm) const {
		return comm->SendData(m_buffer, GetMessageSize());
	}

};

#endif // MESSAGE_H