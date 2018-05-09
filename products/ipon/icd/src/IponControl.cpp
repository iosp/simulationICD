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
#include "TCPCommunication.h"
#include "Periodic1HZMessage.h"
#include "Periodic100HZMessage.h"

IponControl::IponControl(const std::string& confFilePath) {
	m_iponConf = new IponConfig(confFilePath);
}

IponControl::~IponControl() {
	for (auto th : m_messagesThreads) {
		th->interrupt();
	}
	for (auto message : m_messages) {
		delete message.first;
		delete message.second;
	}
	delete m_iponConf;
}

void IponControl::Run() {
	// create the messages
	m_messages.push_back(t_message(new Periodic1HZMessage(m_iponConf->GetPeriodic1MsgHertz()),
									 new UDPCommunication(m_iponConf->GetUDPIPAdrress(), m_iponConf->GetUDPPort())));
	m_messages.push_back(t_message(new Periodic100HZMessage(m_iponConf->GetPeriodic100MsgHertz()), new TCPCommunication(m_iponConf->GetTCPPort())));
	// create threads with messages 
	for (auto message : m_messages) {
		m_messagesThreads.push_back(std::make_shared<boost::thread>(&IponControl::SendThreadMethod, this, message));
	}
}

void IponControl::SetData(const IponData& data) {
	m_IponData_mutex.lock();
	m_data = data;
	m_IponData_mutex.unlock();
}

IponData IponControl::GetData() {
	return m_data;
}

void IponControl::SendThreadMethod(const t_message& message) {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	// extract data from the message
	auto iponMessage = message.first;
	auto comm = message.second;
	// initialize communication
	if (!comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running send thread.\n";
		return;
	}

	try {
		while (true) {
			m_IponData_mutex.lock();
			// DBGLOG << "Going to send data: " << m_data.toString(iponMessage->GetMsgBitID()) << "\n";
			// fill message data
			iponMessage->FillMessage(m_data);
			m_IponData_mutex.unlock();
			// send the message (with the communication ptr)
			iponMessage->SendMessage(comm);

			Utilities::SleepForRestTime(startTime, iponMessage->GetSleepTimeBetweenEverySend());
			startTime = boost::posix_time::microsec_clock::local_time();
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted&) {
        LOG << "thread IPON interruped!\n";
        return;
    } 
}
