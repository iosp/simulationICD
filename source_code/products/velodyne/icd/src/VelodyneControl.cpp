/**
* VelodyneControl.cpp
* Manage communication between velodyne sensor with UDP socket
* Author: Binyamin Appelbaum
* Date: 7.11.17
*/

#include "VelodyneControl.h"
#include "VelodyneConfig.h"
#include "VelodyneMessage.h"
#include "UDPCommunication.h"
#include "LoggerProxy.h"

VelodyneControl::VelodyneControl(const std::string& confFilePath, bool isVelodyne16) : m_isVelodyne16(isVelodyne16) {
	m_velodyneConf = new VelodyneConfig(confFilePath);
    InitCommunication();
}

VelodyneControl::~VelodyneControl() {
    delete m_comm;
    delete m_velodyneConf;
}

void VelodyneControl::InitCommunication() {
    LOG << "Initializing velodyne communication\n";

    m_comm = new UDPCommunication(m_velodyneConf->GetIpAddress(), m_velodyneConf->GetPort());
    if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize UDP communication.\n";
	}
    m_isCommInitialized = true;
    LOG << "Velodyne communication initialized successfully\n";
}

bool VelodyneControl::CheckDataValidation(const VelodyneData& data) const {
    int desiredNumOfBlocks = m_isVelodyne16 ? NUM_OF_VELODYNE_DATA_BLOCKS * 2 : NUM_OF_VELODYNE_DATA_BLOCKS;
    if (data.GetBlocks().size() != desiredNumOfBlocks) {
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
        int desiredNumOfChannelsInBlock = m_isVelodyne16 ? NUM_OF_VELODYNE_DATA_CHANNELS_IN_BLOCK / 2 : NUM_OF_VELODYNE_DATA_CHANNELS_IN_BLOCK;
        if (block.GetChannels().size() != desiredNumOfChannelsInBlock) {
            ERRLOG << "Channels size is not valid: " << block.GetChannels().size() << "\n";
            return false;
        }
    }
    return true;
}

void VelodyneControl::SendData(const VelodyneData& data) {
    if (!m_isCommInitialized) {
        ERRLOG << "Velodyne communication is not initialized! Cannot send data.\n";
        return;
    }
    VelodyneMessage msg((int)m_velodyneConf->GetReturnMode(), (int)m_velodyneConf->GetDataSource(), m_isVelodyne16);
    if (CheckDataValidation(data)) {
        msg.FillMessage(data);
        DBGLOG << "Going to send data: " << data.toString() << "\n";
        msg.SendMessage(m_comm);
    }
    else {
        ERRLOG << "Data is not valid\n";
    }
}

VelodyneData VelodyneControl::ReceiveData() {
    ERRLOG << "This function is not implemented!\n";
    return VelodyneData();
}