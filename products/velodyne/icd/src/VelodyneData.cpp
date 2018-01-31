/*
* VelodyneData.cpp
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include "VelodyneData.h"

VelodyneData::VelodyneData(const std::vector<VLPBlock>& data) : m_data(data){
    
}

VelodyneData::VLPBlock::VLPBlock(double azimuth, const t_channel_data& channels, const boost::posix_time::time_duration& simTime) :
    m_azimuth(azimuth), m_channels(channels), m_simTime(simTime) {
}