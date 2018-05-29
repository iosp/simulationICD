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
}

IdanControl::~IdanControl() {
	m_getDataThread.interrupt();
	m_getDataThread.join();
	delete m_comm;
	delete m_idanConf;
	for (auto message : m_getMessages) {
		delete message;
	}
}

void IdanControl::InitCommunication() {
	m_comm = new CanCommunication(m_idanConf->GetInterfaceName(), m_idanConf->GetBaudRate(), m_idanConf->IsVirtualInterface());
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize CAN communication, not running get thread.\n";
		return;
	}
	InitGetMessages();
	m_isCommInitialized = true;
}

void IdanControl::InitGetMessages() {
	// get messages thread
	m_getMessages.push_back(new HLCPrimaryControlMessage(m_idanConf->GetHLCHertz()));
	m_getMessages.push_back(new HLCSecondaryControlMessage(m_idanConf->GetHLCHertz()));
	m_getDataThread = boost::thread(&IdanControl::GetThreadMethod, this);
}

void IdanControl::SendData(const IdanData& data) {
	if (!m_isCommInitialized) {
		ERRLOG << "Idan couldn't initalize communication. Cannot send data.\n";
		return;
	}
	auto msgType = data.GetCurrMsgType();
	auto msg = GetMsgByType(msgType);
	DBGLOG << "Going to send data: " << data.toString(msgType) << "\n";
	if (msg) {
		msg->FillMessage(data);
		msg->SendMessage(m_comm);
	}
	delete msg;
}

IdanData IdanControl::ReceiveData() {
	return m_data;
}

void IdanControl::GetThreadMethod() {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	
	try {
		while (true) {
			char buffer[1000]{};
			m_comm->GetData(buffer);
			auto message = GetMsgByID(buffer);
			if (message) {
				message->ParseMessage(buffer);
				m_idanData_mutex.lock();
				message->UpdateData(m_data);
				m_idanData_mutex.unlock();
				// make sure the getData will be in the suitable rate
				Utilities::SleepForRestTime(startTime, message->GetSleepTimeBetweenEverySend());
			}
			startTime = boost::posix_time::microsec_clock::local_time();
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted&) {
        LOG << "thread Idan Get interruped!\n";
        return;
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

IdanMessageSend* IdanControl::GetMsgByType(IdanMsgType msgType) const {
	IdanMessageSend* msg = nullptr;
	switch (msgType) {
        case IDAN_PRIMARY:
			msg = new IdanPrimaryMessage();
		  	break;
        case IDAN_SECONDARY_REPORT:
            msg = new IdanSecondaryReportMessage();
            break;
		case IDAN_SECONDARY_SENSOR:
			msg = new IdanSecondarySensorMessage();
			break;
        default:
			ERRLOG << "Something Wrong\n";
            break;
    }
	return msg;
}