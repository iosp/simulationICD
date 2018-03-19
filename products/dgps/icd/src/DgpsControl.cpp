/*
* DgpsControl.cpp
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include "DgpsControl.h"
#include "LoggerProxy.h"
#include "Helper.h"
#include "RSCommunication.h"
#include "DgpsConfig.h"
#include "BestVelMessage.h"
#include "BestPosMessage.h"

DgpsControl::DgpsControl(const std::string& confFilePath) {
	m_dgpsConf = new DgpsConfig(confFilePath);
	m_comm = new RSCommunication(m_dgpsConf->GetPortName(), m_dgpsConf->GetBaudRate());
}

DgpsControl::~DgpsControl() {
	m_sendDataThread.interrupt();
	delete m_dgpsConf;
	delete m_comm;
	for (auto message : m_messages) {
		delete message;
	}
}

void DgpsControl::Run() {
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running send thread.\n";
		return;
	}
	m_messages.push_back(new BestPosMessage(m_dgpsConf->GetHertz()));
	m_messages.push_back(new BestVelMessage(m_dgpsConf->GetHertz()));

	m_sendDataThread = boost::thread(&DgpsControl::SendThreadMethod, this);
}

DgpsData* DgpsControl::GetData() {
	ERRLOG << "This function is not implemented!\n";
    return nullptr;
}

void DgpsControl::SetData(const DgpsData& data) {
	m_dgpsData_mutex.lock();
	m_dgpsDataCollection.push(data);
	m_dgpsData_mutex.unlock();
}

void DgpsControl::SendThreadMethod() {
	boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
	
	while (true) {
		DgpsData data;
		m_dgpsData_mutex.lock();
		bool hasValue = m_dgpsDataCollection.pop(data);
		m_dgpsData_mutex.unlock();
		int timeToSleep = 0;
		
		if (hasValue) {
			DBGLOG << "Going to send data: " << data.toString() << "\n";
			for (auto message : m_messages) {
				message->FillMessage(data);
				SendMessage(message);
				timeToSleep = message->GetSleepTimeBetweenEverySend();
			}
		}

		Utilities::SleepForRestTime(startTime, timeToSleep);
		startTime = boost::posix_time::microsec_clock::local_time();
	}
}

void DgpsControl::SendMessage(IMessage<DgpsData>* message) const {
	bool allSent = false;
	while (!allSent) {
		int bytesSent =	message->SendMessage(m_comm);
		allSent = (bytesSent >= message->GetMessageSize());
		if (!allSent) {
			ERRLOG << "Couldn't send all buffer data. Retrying...\n";
		}
	}
}