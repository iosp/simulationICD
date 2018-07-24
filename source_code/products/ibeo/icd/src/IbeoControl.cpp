/*
* IbeoControl.cpp
* Manage communication between IBEO sensor
* Author: Binyamin Appelbaum
* Date: 23.04.18
*/

#include "IbeoControl.h"
#include "IbeoConfig.h"
#include "IbeoMessage.h"
#include "IbeoData.h"
#include "TCPServerCommunication.h"
#include "LoggerProxy.h"

IbeoControl::IbeoControl(const std::string& confFilePath) {
	m_ibeoConf = new IbeoConfig(confFilePath);
	InitCommunication();
}

IbeoControl::~IbeoControl() {
	delete m_comm;
	delete m_ibeoConf;
}

void IbeoControl::InitCommunication() {
	LOG << "Initializing ibeo communication\n";

	m_comm = new TCPServerCommunication(m_ibeoConf->GetPort());
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize TCP communication.\n";
		return;
	}
	m_isCommInitialized = true;
	LOG << "Ibeo communication initialized successfully\n";
}

void IbeoControl::SendData(const IbeoData& data) {
	if (!m_isCommInitialized) {
		ERRLOG << "Ibeo couldn't initalize communication. Cannot send data.\n";
		return;
	}
	
	IbeoMessage msg(m_ibeoConf->GetTStartAngle(), m_ibeoConf->GetTEndAngle(), m_ibeoConf->GetBStartAngle(), 
					m_ibeoConf->GetBEndAngle(), m_ibeoConf->GetAngleIncrement());

    msg.FillMessage(data);
    DBGLOG << "Going to send data: " << data.toString() << "\n";
    msg.SendMessage(m_comm);
}

IbeoData IbeoControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return IbeoData();
}