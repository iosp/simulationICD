/**
* VLPControl.cpp
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
*/

#include "VLPControl.h"
#include "VLPConfig.h"
#include "VLPMessage.h"
#include "UDPCommunication.h"
#include "LoggerProxy.h"

VLPControl::VLPControl(const std::string& confFilePath) {
	m_vlpConf = new VLPConfig(confFilePath);
    m_comm = new UDPCommunication(m_vlpConf->GetIpAddress(), m_vlpConf->GetPort());
    if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication.\n";
	}
}

VLPControl::~VLPControl() {
    delete m_comm;
    delete m_vlpConf;
}

bool VLPControl::CheckDataValidation(const VelodyneData& data) const {
    if (data.GetBlocks().size() != (NUM_OF_VLP_DATA_BLOCKS * 2)) {
        ERRLOG << "Number of blocks is not valid: " << data.GetBlocks().size() << "\n";
        return false;
    }

    for (const auto& block : data.GetBlocks()) {
        auto azimuth = block.GetAzimuth();
        // avoid above 360 azimuth or negative azimuth
        if ((azimuth >= DEGREES) || (azimuth < 0)) {
            ERRLOG << "Azimuth is not valid: " << azimuth << "\n";
            return false;
        }
        // check that the data size corresponds to the number of columns
        if (block.GetChannels().size() != (NUM_OF_VLP_DATA_CHANNELS_IN_BLOCK / 2)) {
            ERRLOG << "Channels size is not valid: " << block.GetChannels().size() << "\n";
            return false;
        }
    }
    return true;
}

void VLPControl::SendData(const VelodyneData& data) {
    VLPMessage msg((int)m_vlpConf->GetReturnMode(), (int)m_vlpConf->GetDataSource());
    if (CheckDataValidation(data)) {
        msg.FillMessage(data);
        DBGLOG << "Going to send data: " << data.toString() << "\n";
        msg.SendMessage(m_comm);
    }
    else {
        ERRLOG << "Data is not valid\n";
    }
}

VelodyneData VLPControl::ReceiveData() {
    ERRLOG << "This function is not implemented!\n";
    return VelodyneData();
}