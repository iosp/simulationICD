/*
* NovatelControl.cpp
* Manage communication between Novatel sensor
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include "NovatelControl.h"
#include "LoggerProxy.h"
#include "RSCommunication.h"
#include "NovatelConfig.h"
#include "BestVelMessage.h"
#include "BestPosMessage.h"

NovatelControl::NovatelControl(const std::string& confFilePath) {
	m_novatelConf = new NovatelConfig(confFilePath);
	m_comm = new RSCommunication(m_novatelConf->GetPortName(), m_novatelConf->GetBaudRate());
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication.\n";
	}
	else {
		m_initialized = true;
	}
}

NovatelControl::~NovatelControl() {
	delete m_novatelConf;
	delete m_comm;
}

void NovatelControl::SendData(const NovatelData& data) {
	if (!m_initialized) {
		ERRLOG << "Novatel couldn't initalize communication. Cannot send data.\n";
		return;
	}
	auto msgType = data.GetCurrMsgType();
	auto msg = GetMsgByType(msgType);
	DBGLOG << "Going to send data: " << data.toString(msgType) << "\n";
	if (msg) {
		msg->FillMessage(data);
		msg->SendMessage(m_comm);
	}
	// SendMessage(msg); TODO check if necessary
	delete msg;
}

Message<NovatelData>* NovatelControl::GetMsgByType(NovatelMsgType msgType) const {
	Message<NovatelData>* msg = nullptr;
	switch (msgType) {
        case NOVATEL_BEST_POS:
			msg = new BestPosMessage();
		  	break;
        case NOVATEL_BEST_VEL:
            msg = new BestVelMessage();
            break;
        default:
			ERRLOG << "Something Wrong\n";
            break;
    }
	return msg;
}

void NovatelControl::SendMessage(Message<NovatelData>* message) const {
	bool allSent = false;
	while (!allSent) {
		int bytesSent =	message->SendMessage(m_comm);
		allSent = (bytesSent >= message->GetMessageSize());
		if (!allSent) {
			ERRLOG << "Couldn't send all buffer data. Retrying...\n";
		}
	}
}

NovatelData NovatelControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return NovatelData();
}