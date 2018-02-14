/*
* InsControl.cpp
* Manage communication of INS sensor
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include "InsControl.h"
#include "InsConfig.h"
#include "InsMessage.h"
#include "Logger.h"
#include "Helper.h"

InsControl::InsControl(const std::string& confFilePath) {
	m_insConf = new InsConfig(confFilePath);
}

InsControl::~InsControl() {
	delete m_insConf;
}

void InsControl::SendThreadMethod(InsMessage* message) {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	
	while (true) {
		m_insData_mutex.lock();
		DBGLOG << "Going to send data: " << m_data.toString() << "\n";
		message->FillMessage(m_data);
		// send the message
		m_insData_mutex.unlock();

		Utilities::SleepForRestTime(startTime, message->GetSleepTimeBetweenEverySend());
		startTime = boost::posix_time::microsec_clock::local_time();
	}
}

void InsControl::SetData(const InsData& data) {
	m_insData_mutex.lock();
	m_data = data;
	m_insData_mutex.unlock();
}

void InsControl::Run() {
	// if (!m_comm->Init()) {
	// 	ERRLOG << "Failed to initialize communication, not running send thread.\n";
	// 	return;
	// }
	// m_sendDataThread = boost::thread(&InsControl::SendThreadMethod, this);
}

InsData* InsControl::GetData() {
	ERRLOG << "This function is not implemented!\n";
    return nullptr;
}