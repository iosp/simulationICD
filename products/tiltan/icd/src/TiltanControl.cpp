/*
* TiltanControl.cpp
* Manage communication of Tiltan sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include "TiltanControl.h"
#include "TiltanConfig.h"
#include "UDPCommunication.h"
#include "TCPCommunication.h"
#include "StatusMessage.h"
#include "NavigationDataMessage.h"
#include "InternalGPSMessage.h"
#include "ErrorsEstimationMessage.h"
#include "LoggerProxy.h"


TiltanControl::TiltanControl(const std::string& confFilePath) {
	m_tiltanConf = new TiltanConfig(confFilePath);
}

TiltanControl::~TiltanControl() {
	delete m_tiltanConf;
	for (auto message : m_messages) {
		delete message.first;
		delete message.second;
	}
}

void TiltanControl::InitCommunication() {
	m_messages.push_back(t_message(new StatusMessage(), new TCPCommunication(m_tiltanConf->GetStatusMsgPort())));
	m_messages.push_back(t_message(new NavigationDataMessage(),
									 new UDPCommunication(m_tiltanConf->GetNavigationDataMsgIpAddress(), m_tiltanConf->GetNavigationDataMsgPort())));
	m_messages.push_back(t_message(new InternalGPSMessage(),
									 new UDPCommunication(m_tiltanConf->GetInternalGPSMsgIpAddress(), m_tiltanConf->GetInternalGPSMsgPort())));
	m_messages.push_back(t_message(new ErrorsEstimationMessage(),
									 new UDPCommunication(m_tiltanConf->GetErrorsEstimationMsgIpAddress(), m_tiltanConf->GetErrorsEstimationMsgPort())));
	// initialize communications
	for (auto message : m_messages) {
		if (!message.second->Init()) {
			ERRLOG << "Failed to initialize communication of message " << message.first->GetMsgType() << "\n";
			return;
		}
	}
	m_isCommInitialized = true;
}

void TiltanControl::SendData(const TiltanData& data) {
	if (!m_isCommInitialized) {
		ERRLOG << "Tiltan couldn't initalize all its communications. Cannot send data\n";
		return;
	}
	auto msgType = data.GetCurrMsgType();
	auto pair = GetMsgByType(msgType);
	auto tiltanMessage = pair.first;
	auto comm = pair.second;
	DBGLOG << "Going to send data: " << data.toString(msgType) << "\n";
	if (tiltanMessage && comm) { // avoid nullptr usage
		tiltanMessage->FillMessage(data);
		tiltanMessage->SendMessage(comm);
		tiltanMessage->InitMessage();
	}
}

TiltanControl::t_message TiltanControl::GetMsgByType(TiltanMsgType msgType) const {
	for (auto message : m_messages) {
		if (message.first->GetMsgType() == msgType) {
			return message;
		}
	}
	ERRLOG << "Didn't find msg type, something wrong occurred\n";
	return t_message();
}

TiltanData TiltanControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return TiltanData();
}