#ifndef IPON_MESSAGE_H
#define IPON_MESSAGE_H

/*
* IponMessage.h
* Ipon message to send
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "IMessage.h"
#include "IponData.h"
#include "IponStructs.h"
#include <string.h> // memcpy

class ICommunication; // forward declaration

class IponMessage : public IMessage<IponData>{
protected:
	template <class Data>
	void CopyDataToBuffer(const Data* data, size_t sizeOfData, int& offset) {
		memcpy(m_buffer + offset, data, sizeOfData);
		offset += sizeOfData;
	}
public:
	IponMessage(float hertz);

	virtual ~IponMessage() = default;

	virtual int SendMessage(ICommunication* comm) const override;

    void InitMessage();
};

#endif // IPON_MESSAGE_H