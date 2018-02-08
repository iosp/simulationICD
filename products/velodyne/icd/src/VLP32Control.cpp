/*
* VLP32Control.cpp
* Manage communication between velodyne sensor with UDP socket - for VLP 32
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "VLP32Control.h"

VLP32Control::VLP32Control(const std::string& confFilePath) : VLPControl(confFilePath) {

}
void VLP32Control::FillDataRecords(VLPDataPacket& packet, int dataIndex, int packetIndex) const {
    auto values = MapChannels(m_velodyneData[dataIndex].GetChannels());

    FillChannelsInPacket(packet, values, packetIndex);
}

bool VLP32Control::CanAddToPacket(const boost::posix_time::time_duration& lastDuration, int dataIndex) const {
    return (lastDuration < m_velodyneData[dataIndex].GetSimTime() && !IsDataZeroed(dataIndex));
}

int VLP32Control::DataIndexIncrement() const {
    return 1;
}

int VLP32Control::GetNumOfrowsInColumn() const {
    return 32;
}