/*
* VelodyneData.cpp
* 
* Author: Binyamin Appelbaum
* Date: 10.01.18
* 
*/

#include "VelodyneData.h"
#include <sstream>

void VelodyneData::AddBlock(const VelodyneBlock& block) {
    m_blocks.push_back(block);
}

std::string VelodyneData::toString() const {
    std::stringstream ss;
    ss << std::endl;
    for (auto const& block : m_blocks) {
        ss << "Azimuth: " << block.GetAzimuth() << std::endl;
        for (auto const& channel : block.GetChannels()) {
            ss << "(" << channel.first << "," << channel.second << ") ";
        }
        ss << std::endl << "Simulation time: " << block.GetSimTime() << std::endl;
    }
   
    return ss.str();
 }