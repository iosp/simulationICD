/*
* IponMessage.cpp
* Ibeo message to send
* Author: Binyamin Appelbaum
* Date: 03.05.18
*/

#include "IponMessage.h"
#include "ICommunication.h"

IponMessage::IponMessage(float hertz) : IMessage(hertz) {

}

int IponMessage::SendMessage(ICommunication* comm) const {
	return comm->SendData(m_buffer, GetMessageSize());
}