#ifndef IPON_MESSAGE_H
#define IPON_MESSAGE_H

/*
* IponMessage.h
* Ipon message to send
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include "Message.h"
#include <string.h> // memcpy

class IponData;
enum IponMsgType : unsigned int; // forward declaration of enum must specify underlying type (c++0x)

class IponMessage : public Message<IponData> {
protected:
	template <class Data>
	void CopyDataToBuffer(const Data* data, size_t sizeOfData, int& offset) {
		memcpy(m_buffer + offset, data, sizeOfData);
		offset += sizeOfData;
	}
public:
	IponMessage() = default;

	virtual ~IponMessage() = default;

	virtual IponMsgType GetMsgType() const = 0;
};

#endif // IPON_MESSAGE_H