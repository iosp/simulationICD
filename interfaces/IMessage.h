#ifndef IMESSAGE_H
#define IMESSAGE_H

/*
* IMessage.h
* Message interface
* Author: Binyamin Appelbaum
* Date: 06.03.18
*/

static const int BUFFER_SIZE = 1000;

class ICommunication; // forward declaration

template <class TData>
class IMessage {
protected:

	int m_sleepTimeBetweenEverySend;

	char m_buffer[BUFFER_SIZE]{0};

public:
	IMessage(int hertz) {
		m_sleepTimeBetweenEverySend = (hertz != 0 ) ? (1e6 / hertz) : 0; 
	}

	virtual ~IMessage() = default;

	virtual int GetMessageSize() const = 0;

	virtual void FillMessage(const TData& data) = 0;

	virtual int SendMessage(ICommunication* comm) const = 0;

	int GetSleepTimeBetweenEverySend() const { return m_sleepTimeBetweenEverySend; }
};

#endif // IMESSAGE_H