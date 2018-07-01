/*
* IponControl.cpp
* Manage communication between IPON sensor
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponControl.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include "IponConfig.h"
#include "UDPCommunication.h"
#include "TCPServerCommunication.h"
#include "Periodic1HZMessage.h"
#include "Periodic100HZMessage.h"

IponControl::IponControl(const std::string& confFilePath) {
	m_iponConf = new IponConfig(confFilePath);
	InitCommunication();
}

IponControl::~IponControl() {
	for (auto message : m_messages) {
		delete message.first;
		delete message.second;
	}
	delete m_iponConf;
}

void IponControl::InitCommunication() {
	LOG << "Initializing ipon communication\n";
	// create the messages
	m_messages.push_back(t_message(new Periodic1HZMessage(),
									 new UDPCommunication(m_iponConf->GetUDPIPAdrress(), m_iponConf->GetUDPPort())));
	m_messages.push_back(t_message(new Periodic100HZMessage(), new TCPServerCommunication(m_iponConf->GetTCPPort())));

	// initialize communications
	for (auto message : m_messages) {
		if (!message.second->Init()) {
			ERRLOG << "Failed to initialize communication of message.\n";
			return;
		}
	}
	m_isCommInitialized = true;
	LOG << "Ipon communication initialized successfully\n";
}

void IponControl::SendData(const IponData& data) {
	if (!m_isCommInitialized) {
		ERRLOG << "IPON couldn't initalize all its communications. Cannot send data\n";
		return;
	}
	auto msgType = data.GetCurrMsgType();
	auto pair = GetMsgByType(msgType);
	auto iponMessage = pair.first;
	auto comm = pair.second;
	DBGLOG << "Going to send data: " << data.toString(msgType) << "\n";
	if (iponMessage && comm) { // avoid nullptr usage
		iponMessage->FillMessage(data);
		iponMessage->SendMessage(comm);
		iponMessage->InitMessage();
	}
}

IponControl::t_message IponControl::GetMsgByType(IponMsgType msgType) const {
	for (auto message : m_messages) {
		if (message.first->GetMsgType() == msgType) {
			return message;
		}
	}
	ERRLOG << "Didn't find msg type, something wrong occurred\n";
	return t_message();
}

IponData IponControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return IponData();
}