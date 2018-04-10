/*
* IdanData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 20.03.18
* 
*/

#include "IdanData.h"
#include <sstream>

std::string IdanData::toString() const {
    std::stringstream ss;
    ss << "m_IDANPrimary - steer pose: " << m_IDANPrimary.steerPose << ". gasPose: " << m_IDANPrimary.gasPose;
    
    return ss.str();
}