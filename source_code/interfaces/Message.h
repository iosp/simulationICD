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

static const int BUFFER_SIZE = 2048;

template <class TData>
class Message {
protected:
	char m_buffer[BUFFER_SIZE];

public:
	Message() = default;

	virtual ~Message() = default;

	virtual int GetMessageSize() const = 0;

	/**
	 * Fill message's buffer with the input data
	 * @param data - the message's data
	 */ 
	virtual void FillMessage(const TData& data) = 0;

	/**
	 * Initialize the buffer of the message
	 */ 
	virtual void InitMessage() {
		memset(m_buffer, 0, BUFFER_SIZE);
	}

	/**
	 * Send the message's buffer using the communication input
	 * @param comm - communication protocol
	 * @return - num of bytes that have been sent
	 */ 
	virtual int SendMessage(ICommunication* comm) const {
		return comm->SendData(m_buffer, GetMessageSize());
	}

};

#endif // MESSAGE_H