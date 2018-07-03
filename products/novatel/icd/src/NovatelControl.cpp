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
	InitCommunication();
}

NovatelControl::~NovatelControl() {
	delete m_novatelConf;
	delete m_comm;
}

void NovatelControl::InitCommunication() {
	LOG << "Initializing novatel communication\n";

	m_comm = new RSCommunication(m_novatelConf->GetPortName(), m_novatelConf->GetBaudRate());
	if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize RS communication.\n";\
		return;
	}
	m_isCommInitialized = true;
	LOG << "Novatel communication initialized successfully\n";
}

void NovatelControl::SendData(const NovatelData& data) {
	if (!m_isCommInitialized) {
		ERRLOG << "Novatel communication is not initialized! Cannot send data.\n";
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

NovatelData NovatelControl::ReceiveData() {
	ERRLOG << "This function is not implemented!\n";
    return NovatelData();
}