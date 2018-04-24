/*
* EchoMessage.cpp
* INS echo message to send
* Author: Binyamin Appelbaum
* Date: 27.02.18
*/

#include "EchoMessage.h"
#include "InsData.h"
#include <cstring>  // memset, memcpy

EchoMessage::EchoMessage(float hertz) : InsMessage(hertz) {

}

void EchoMessage::FillMessage(const InsData& data) {
	INS_Echo_Message msg;
	FillHeader(msg.Header);
	memcpy(m_buffer, &msg, sizeof(msg));
}

void EchoMessage::FillHeader(/* out */ INS_HEADER& header) const {
	header.Unit_Code = 0x3c;
	strncpy((char*)header.Operation_Code, "\x00\x00", 2); // 0x0000
	header.Length = 0;
}

int EchoMessage::GetMessageSize() const {
	return sizeof(INS_Echo_Message);
}