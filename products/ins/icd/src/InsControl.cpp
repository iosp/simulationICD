/*
* InsControl.cpp
* Manage communication of INS sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include "InsControl.h"
#include "InsConfig.h"
#include "UDPCommunication.h"
#include "TCPCommunication.h"
#include "StatusMessage.h"
#include "NavigationDataMessage.h"
#include "InternalGPSMessage.h"
#include "ErrorsEstimationMessage.h"
#include "LoggerProxy.h"


InsControl::InsControl(const std::string& confFilePath) {
	m_insConf = new InsConfig(confFilePath);
	InitializeMessages();
}

InsControl::~InsControl() {
	delete m_insConf;
	for (auto message : m_messages) {
		delete message.first;
		delete message.second;
	}
}

void InsControl::InitializeMessages() {
	m_messages.push_back(t_message(new StatusMessage(), new TCPCommunication(m_insConf->GetStatusMsgPort())));
	m_messages.push_back(t_message(new NavigationDataMessage(),
									 new UDPCommunication(m_insConf->GetNavigationDataMsgIpAddress(), m_insConf->GetNavigationDataMsgPort())));
	m_messages.push_back(t_message(new InternalGPSMessage(),
									 new UDPCommunication(m_insConf->GetInternalGPSMsgIpAddress(), m_insConf->GetInternalGPSMsgPort())));
	m_messages.push_back(t_message(new ErrorsEstimationMessage(),
									 new UDPCommunication(m_insConf->GetErrorsEstimationMsgIpAddress(), m_insConf->GetErrorsEstimationMsgPort())));
	// initialize communications
	for (auto message : m_messages) {
		if (!message.second->Init()) {
			ERRLOG << "Failed to initialize communication of message " << message.first->GetMsgType() << "\n";
			return;
		}
	}
	m_initialized = true;
}

void InsControl::SendData(const InsData& data) {
	if (!m_initialized) {
		ERRLOG << "INS couldn't initalize all its communications. Cannot send data\n";
		return;
	}
	auto msgType = data.GetCurrMsgType();
	auto pair = GetMsgByType(msgType);
	auto insMessage = pair.first;
	auto comm = pair.second;
	DBGLOG << "Going to send data: " << data.toString(msgType) << "\n";
	if (insMessage && comm) { // avoid nullptr usage
		insMessage->FillMessage(data);
		insMessage->SendMessage(comm);
		insMessage->InitMessage();
	}

}

InsControl::t_message InsControl::GetMsgByType(InsMsgType msgType) const {
	for (auto message : m_messages) {
		if (message.first->GetMsgType() == msgType) {
			return message;
		}
	}
	ERRLOG << "Didn't find msg type, something wrong occurred\n";
	return t_message();
}

InsData InsControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return InsData();
}