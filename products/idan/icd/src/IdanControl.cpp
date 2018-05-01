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
#include <boost/assign.hpp> // boost::assign::map_list_of

// map message ID to bitwise representation, for toString method
const std::map<t_msgID, std::bitset<8> > MsgIdToBit = 
            boost::assign::map_list_of(HLC_PRIM_ID, HLC_PRIM_BIT)(HLC_SEC_ID, HLC_SEC_BIT)(IDAN_PRIM_ID, IDAN_PRIM_BIT)
									  (IDAN_SEC_REP_ID, IDAN_SEC_REP_BIT)(IDAN_SEC_SEN_ID, IDAN_SEC_SEN_BIT);

IdanControl::IdanControl(const std::string& confFilePath) {
	m_idanConf = new IdanConfig(confFilePath);
	m_comm = new CanCommunication(m_idanConf->GetInterfaceName(), m_idanConf->GetBaudRate(), m_idanConf->IsVirtualInterface());
}

IdanControl::~IdanControl() {
	m_getDataThread.interrupt();
	m_getDataThread.join();
	for (auto th : m_messagesThreads) {
		th->interrupt();
	}
	for (auto th : m_messagesThreads) {
		th->join();
	}
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

void IdanControl::SendThreadMethod(IdanMessageSend* message) {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	try {
		while (true) {
			m_idanData_mutex.lock();
			DBGLOG << "Going to send data:\n" << m_data.toString(Utilities::GetValFromMap(MsgIdToBit, message->GetMsgID(), std::bitset<8>())) << "\n";
			// fill message data
			message->FillMessage(m_data);
			m_idanData_mutex.unlock();
			// send the message (with the communication ptr)
			message->SendMessage(m_comm); // TODO mutex on m_comm ?!
			// make sure the message will be sent in the suitable rate
			Utilities::SleepForRestTime(startTime, message->GetSleepTimeBetweenEverySend());
			startTime = boost::posix_time::microsec_clock::local_time();
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted&) {
        LOG << "thread Idan Send interruped!\n";
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