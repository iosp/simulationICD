/*
* DgpsControl.cpp
* Manage communication between DGPS sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include "DgpsControl.h"
#include "LoggerProxy.h"
#include "RSCommunication.h"
#include "DgpsConfig.h"
#include "BestVelMessage.h"
#include "BestPosMessage.h"

DgpsControl::DgpsControl(const std::string& confFilePath) {
	m_dgpsConf = new DgpsConfig(confFilePath);
	m_comm = new RSCommunication(m_dgpsConf->GetPortName(), m_dgpsConf->GetBaudRate());
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication.\n";
	}
}

DgpsControl::~DgpsControl() {
	delete m_dgpsConf;
	delete m_comm;
}

void DgpsControl::SendData(const DgpsData& data) {
	auto msg = GetMsgByType(data.GetCurrMsgType());
	msg->FillMessage(data);
	msg->SendMessage(m_comm);
	// SendMessage(msg); TODO check if necessary
}

Message<DgpsData>* DgpsControl::GetMsgByType(DgpsMsgType msgType) const {
	Message<DgpsData>* msg = nullptr;
	switch (msgType) {
        case DGPS_BEST_POS:
			msg = new BestPosMessage();
		  	break;
        case DGPS_BEST_VEL:
            msg = new BestVelMessage();
            break;
        default:
			ERRLOG << "Something Wrong\n";
            break;
    }
	return msg;
}

void DgpsControl::SendMessage(Message<DgpsData>* message) const {
	bool allSent = false;
	while (!allSent) {
		int bytesSent =	message->SendMessage(m_comm);
		allSent = (bytesSent >= message->GetMessageSize());
		if (!allSent) {
			ERRLOG << "Couldn't send all buffer data. Retrying...\n";
		}
	}
}

DgpsData DgpsControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return DgpsData();
}