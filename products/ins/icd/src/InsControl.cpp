/*
* InsControl.cpp
* Manage communication of INS sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include "InsControl.h"
#include "InsConfig.h"
#include "InsMessage.h"
#include "UDPCommunication.h"
#include "TCPCommunication.h"
#include "LoggerProxy.h"
#include "StatusMessage.h"
#include "NavigationDataMessage.h"
#include "InternalGPSMessage.h"
#include "ErrorsEstimationMessage.h"
#include "EchoMessage.h"
#include "Helper.h"


InsControl::InsControl(const std::string& confFilePath) {
	m_insConf = new InsConfig(confFilePath);
}

InsControl::~InsControl() {
	for (auto th : m_messagesThreads) {
		th->interrupt();
	}
	for (auto message : m_messages) {
		delete message.first;
		delete message.second;
	}
	delete m_insConf;
}

void InsControl::SendThreadMethod(const t_message& message) {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	// extract data from the message
	auto insMessage = message.first;
	auto comm = message.second;
	// initialize communication
	if (!comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running send thread.\n";
		return;
	}

	while (true) {
		m_insData_mutex.lock();
		DBGLOG << "Going to send data: " << m_data.toString() << "\n";
		// fill message data
		insMessage->FillMessage(m_data);
		m_insData_mutex.unlock();
		// send the message (with the communication ptr)
		insMessage->SendMessage(comm);

		Utilities::SleepForRestTime(startTime, insMessage->GetSleepTimeBetweenEverySend());
		startTime = boost::posix_time::microsec_clock::local_time();
	}
}

void InsControl::SetData(const InsData& data) {
	m_insData_mutex.lock();
	m_data = data;
	m_insData_mutex.unlock();
}

void InsControl::Run() {
	// create the messages
	m_messages.push_back(t_message(new StatusMessage(m_insConf->GetStatusMsgHz()),
									 new TCPCommunication(m_insConf->GetStatusMsgIpAddress(), m_insConf->GetStatusMsgPort())));
	m_messages.push_back(t_message(new NavigationDataMessage(m_insConf->GetNavigationDataMsgHz()),
									 new UDPCommunication(m_insConf->GetNavigationDataMsgIpAddress(), m_insConf->GetNavigationDataMsgPort())));
	m_messages.push_back(t_message(new InternalGPSMessage(m_insConf->GetInternalGPSMsgHz()),
									 new UDPCommunication(m_insConf->GetInternalGPSMsgIpAddress(), m_insConf->GetInternalGPSMsgPort())));
	m_messages.push_back(t_message(new ErrorsEstimationMessage(m_insConf->GetErrorsEstimationMsgHz()),
									 new UDPCommunication(m_insConf->GetErrorsEstimationMsgIpAddress(), m_insConf->GetErrorsEstimationMsgPort())));
	// create threads with messages 
	for (auto message : m_messages) {
		m_messagesThreads.push_back(std::make_shared<boost::thread>(&InsControl::SendThreadMethod, this, message));
	}
}

InsData* InsControl::GetData() {
	ERRLOG << "This function is not implemented!\n";
    return nullptr;
}