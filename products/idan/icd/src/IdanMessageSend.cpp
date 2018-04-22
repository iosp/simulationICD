/*
* IdanMessageSend.cpp
* IDAN message to send
* Author: Binyamin Appelbaum
* Date: 29.03.18
*/

#include "IdanMessageSend.h"
#include "LoggerProxy.h"
#include "ICommunication.h"

IdanMessageSend::IdanMessageSend(int hertz) : IdanMessage(hertz) {
}

int IdanMessageSend::SendMessage(ICommunication* comm) const {
    return comm->SendData(m_buffer, GetMessageSize());
}