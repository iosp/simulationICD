/*
* VLP16Control.cpp
* Manage communication between velodyne sensor with UDP socket - for VLP 16
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/

#include "VLP16Control.h"

VLP16Control::VLP16Control(const VLPConfig& vlpConfig) : VLPControl(vlpConfig) {
}

void VLP16Control::FillDataRecords(VLPDataPacket& packet, int dataIndex, int packetIndex) const {
    auto values = MapChannels(m_velodyneData[dataIndex].GetChannels());

    auto additionalValues = MapChannels(m_velodyneData[dataIndex + 1].GetChannels());
    values.insert(values.end(), additionalValues.begin(), additionalValues.end());

    FillChannelsInPacket(packet, values, packetIndex);
}

bool VLP16Control::CanAddToPacket(const boost::posix_time::time_duration& lastDuration, int dataIndex) const {
    return (lastDuration < m_velodyneData[dataIndex].GetSimTime()) && 
                (m_velodyneData[dataIndex].GetSimTime() < m_velodyneData[dataIndex + 1].GetSimTime()) &&
                !IsDataZeroed(dataIndex);
}

int VLP16Control::DataIndexIncrement() const {
    return 2;
}

int VLP16Control::GetNumOfrowsInColumn() const {
    return 16;
}