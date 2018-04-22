/*
* VelodyneData.cpp
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include "VelodyneData.h"
#include <sstream>

VelodyneData::VelodyneData(double azimuth, const t_channel_data& channels, float simTime) : m_azimuth(azimuth), 
        m_channels(channels), m_simTime(simTime) {

}

 std::string VelodyneData::toString() const {
    std::stringstream ss;
    ss << "Azimuth: " << m_azimuth << std::endl;
    for (auto const& channel : m_channels) {
        ss << "(" << channel.first << "," << channel.second << ") ";
    }
    ss << std::endl << "Simulation time: " << m_simTime;
    
    return ss.str();
 }