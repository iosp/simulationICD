/*
* IdanMessageSend.cpp
* IDAN message to send
* Author: Binyamin Appelbaum
* Date: 29.03.18
*/

#include "IdanMessageSend.h"
#include "LoggerProxy.h"
#include "ICommunication.h"

IdanMessageSend::IdanMessageSend(int hertz) {
	if (hertz == 0) {
		ERRLOG << "Invalid hertz argument for IDAN message\n";
		return;
	}
	m_sleepTimeBetweenEverySend = 1e6 / hertz;
}

int IdanMessageSend::SendMessage(ICommunication* comm) const {
    return comm->SendData(m_buffer, GetMessageSize());
}