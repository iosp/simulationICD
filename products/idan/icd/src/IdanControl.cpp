/*
* IdanControl.cpp
* Manage communication between Idan sensor
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "IdanControl.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include "CanCommunication.h"
#include "IdanConfig.h"
#include "HLCPrimaryControlMessage.h"
#include "HLCSecondaryControlMessage.h"
#include "IdanPrimaryMessage.h"
#include "IdanSecondaryReportMessage.h"
#include "IdanSecondarySensorMessage.h"

IdanControl::IdanControl(const std::string& confFilePath) {
	m_idanConf = new IdanConfig(confFilePath);
	m_comm = new CanCommunication(m_idanConf->GetInterfaceName(), m_idanConf->GetBaudRate(), m_idanConf->IsVirtualInterface());
}

IdanControl::~IdanControl() {
	m_getDataThread.interrupt();
	delete m_comm;
	delete m_idanConf;
	for (auto message : m_getMessages) {
		delete message;
	}
	for (auto message : m_sendMessages) {
		delete message;
	}
}

void IdanControl::Run() {
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running get thread.\n";
		return;
	}
	// get messages thread
	m_getMessages.push_back(new HLCPrimaryControlMessage(m_idanConf->GetHLCHertz()));
	m_getMessages.push_back(new HLCSecondaryControlMessage(m_idanConf->GetHLCHertz()));
	m_getDataThread = boost::thread(&IdanControl::GetThreadMethod, this);

	// send messages thread
	m_sendMessages.push_back(new IdanPrimaryMessage(m_idanConf->GetIdanPrimHertz()));
	m_sendMessages.push_back(new IdanSecondaryReportMessage(m_idanConf->GetIdanSecRepHertz()));
	m_sendMessages.push_back(new IdanSecondarySensorMessage(m_idanConf->GetIdanSecSenHertz()));
	for (auto message : m_sendMessages) {
		m_messagesThreads.push_back(std::make_shared<boost::thread>(&IdanControl::SendThreadMethod, this, message));
	}
}

void IdanControl::SetData(const IdanData& data) {
	m_idanData_mutex.lock();
	m_data = data;
	m_idanData_mutex.unlock();
}

IdanData IdanControl::GetData() {
	return m_data;
}

void IdanControl::GetThreadMethod() {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	
	while (true) {
		char buffer[1000]{};
		m_comm->GetData(buffer);
		auto message = GetMsgByID(buffer);
		if (message) {
			message->ParseMessage(buffer);
			m_idanData_mutex.lock();
			message->UpdateData(m_data);
			m_idanData_mutex.unlock();
			Utilities::SleepForRestTime(startTime, message->GetSleepTimeBetweenEverySend());
		}
		startTime = boost::posix_time::microsec_clock::local_time();
	}
}

void IdanControl::SendThreadMethod(IdanMessageSend* message) {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	while (true) {
		m_idanData_mutex.lock();
		DBGLOG << "Going to send data: " << m_data.toString() << "\n";
		// fill message data
		message->FillMessage(m_data);
		m_idanData_mutex.unlock();
		// send the message (with the communication ptr)
		message->SendMessage(m_comm); // TODO nutex on m_comm ?!

		Utilities::SleepForRestTime(startTime, message->GetSleepTimeBetweenEverySend());
		startTime = boost::posix_time::microsec_clock::local_time();
	}
}

IdanMessageGet* IdanControl::GetMsgByID(const char* buffer) {
	t_msgID id;
	memcpy(&id, buffer, sizeof(id));
	for (auto const& message : m_getMessages) {
		if (message->GetMsgID() == id) {
			DBGLOG << "Msg with id: " << id << " found\n";
			return message;
		}
	}
	return nullptr;
}