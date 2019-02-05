/*
* IdanControl.cpp
* Manage communication between Idan sensor
* Author: Binyamin Appelbaum
* Date: 20.03.18
*/

#include "IdanControl.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include "TCPServerCommunication.h"
#include "NewTCP.h"
#include "IdanConfig.h"
#include "HLCPrimaryControlMessage.h"
#include "HLCSecondaryControlMessage.h"
#include "IdanPrimaryMessage.h"
#include "IdanSecondaryReportMessage.h"
#include "IdanSecondarySensorMessage.h"
#ifdef __linux__
	#include "CanCommunication.h"
#endif

IdanControl::IdanControl(const std::string& confFilePath) {
	m_idanConf = new IdanConfig(confFilePath);
	InitCommunication();
}

IdanControl::~IdanControl() {
	m_isThreadOn = false;
	m_getDataThread.join();
	delete m_comm;
	delete m_idanConf;
	for (auto message : m_getMessages) {
		delete message;
	}
}

void IdanControl::InitCommunication() {
	LOG << "Initializing idan communication\n";

	if (m_idanConf->IsCanView()) {
		m_comm = new NewTCP(m_idanConf->GetTCPPort());
		//m_comm = new TCPServerCommunication(m_idanConf->GetTCPPort());
	}
	else {
		#ifdef __linux__
			m_comm = new CanCommunication(m_idanConf->GetInterfaceName(), m_idanConf->GetBaudRate(), m_idanConf->IsVirtualInterface());
		#elif _WIN32
			ERRLOG << "no communication can be initialized for idan\n";
			return;
		#endif
	}

	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize Idan communication, not running get thread.\n";
		return;
	}
	
	InitGetMessages();
	m_isCommInitialized = true;
	LOG << "Idan communication initialized successfully\n";
}

void IdanControl::InitGetMessages() {
	// get messages thread
	m_getMessages.push_back(new HLCPrimaryControlMessage(m_idanConf->GetHLCHertz(), m_idanConf->IsCanView()));
	m_getMessages.push_back(new HLCSecondaryControlMessage(m_idanConf->GetHLCHertz(), m_idanConf->IsCanView()));
	m_getDataThread = std::thread(&IdanControl::GetThreadMethod, this);
}

void IdanControl::SendData(const IdanData& data) {
	if (!m_isCommInitialized) {
		ERRLOG << "Idan didn't initialize communication. Cannot send data.\n";
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
	
	while (m_isThreadOn) {
		char buffer[1000];
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
	}
}

IdanMessageGet* IdanControl::GetMsgByID(const char* buffer) {
	t_msgID id;
	if (m_idanConf->IsCanView()) {
		id = buffer[4] + (buffer[3] << 8);
	}
	else {
		memcpy(&id, buffer, sizeof(id));
	} 
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
			msg = new IdanPrimaryMessage(m_idanConf->IsCanView());
		  	break;
        case IDAN_SECONDARY_REPORT:
            msg = new IdanSecondaryReportMessage(m_idanConf->IsCanView());
            break;
		case IDAN_SECONDARY_SENSOR:
			msg = new IdanSecondarySensorMessage(m_idanConf->IsCanView());
			break;
        default:
			ERRLOG << "Something Wrong\n";
            break;
    }
	return msg;
}