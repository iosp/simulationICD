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

#include <boost/range/irange.hpp> // boost::irange
#include <boost/assign.hpp> // boost::assign::map_list_of

VLPControl::VLPControl(const std::string& confFilePath) {
	m_vlpConf = new VLPConfig(confFilePath);
    float hertz = (m_vlpConf->GetSensorFrequency() * DEGREES) /
                                    (m_vlpConf->GetHorizontalResolution() * 2*NUM_OF_VLP_DATA_BLOCKS);
    m_message = new VLPMessage(hertz, (int)m_vlpConf->GetReturnMode(), (int)m_vlpConf->GetDataSource());
    m_comm = new UDPCommunication(m_vlpConf->GetIpAddress(), m_vlpConf->GetPort());
    if (!m_comm->Init()) {
		ERRLOG << "Failed to initialize communication, not running send thread.\n";
	}
}

VLPControl::~VLPControl() {
    delete m_comm;
    delete m_vlpConf;
    delete m_message;
}

bool VLPControl::CheckDataValidation(const VelodyneData& data) const {
    if (data.GetBlocks().size() != 24) {
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
        if (block.GetChannels().size() != 16) {
            ERRLOG << "Channels size is not valid: " << block.GetChannels().size() << "\n";
            return false;
        }
    }
    return true;
}

void VLPControl::SetData(const VelodyneData& data) {
    if (CheckDataValidation(data)) {
        m_message->FillMessage(data);
        DBGLOG << "Going to send data: " << data.toString() << "\n";
        m_message->SendMessage(m_comm);
        m_message->InitMessage();
    }
    else {
        ERRLOG << "Data is not valid\n";
    }
}

VelodyneData VLPControl::GetData() {
    ERRLOG << "This function is not implemented!\n";
    return VelodyneData();
}