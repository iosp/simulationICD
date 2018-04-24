/*
* IbeoControl.cpp
* Manage communication between IBEO sensor
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "IbeoControl.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include "IbeoConfig.h"
#include "IbeoMessage.h"
#include "TCPCommunication.h"

IbeoControl::IbeoControl(const std::string& confFilePath) {
	m_ibeoConf = new IbeoConfig(confFilePath);
	m_comm = new TCPCommunication(m_ibeoConf->GetIpAddress(), m_ibeoConf->GetPort());
}

IbeoControl::~IbeoControl() {
	m_sendDataThread.interrupt();
    m_sendDataThread.join();
	delete m_message;
	delete m_comm;
	delete m_ibeoConf;
}

void IbeoControl::Run() {
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running get thread.\n";
		return;
	}

	m_message = new IbeoMessage(m_ibeoConf->GetHertz());
    m_sendDataThread = boost::thread(&IbeoControl::SendThreadMethod, this);
}

void IbeoControl::SetData(const IbeoData& data) {
	m_ibeoData_mutex.lock();
	m_data = data;
	m_ibeoData_mutex.unlock();
}

IbeoData IbeoControl::GetData() {
	return m_data;
}

void IbeoControl::SendThreadMethod() {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	try {
		while (true) {
			m_ibeoData_mutex.lock();
			DBGLOG << "Going to send data: " << m_data.toString() << "\n";
			// fill message data
			m_message->FillMessage(m_data);
			m_ibeoData_mutex.unlock();
			// send the message (with the communication ptr)
			m_message->SendMessage(m_comm); // TODO mutex on m_comm ?!
			m_message->InitMessage();
			// make sure the message will be sent in the suitable rate
			Utilities::SleepForRestTime(startTime, m_message->GetSleepTimeBetweenEverySend());
			startTime = boost::posix_time::microsec_clock::local_time();
			boost::this_thread::interruption_point();
		}
	}
	catch (boost::thread_interrupted&) {
        LOG << "thread IBEO Send interruped!\n";
        return;
    } 
}

