/*
* InsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "InsData.h"
#include <sstream>

InsData::InsData(const boost::posix_time::time_duration& simTime) : m_simTime(simTime){
    
}

std::string InsData::toString() const {
    std::stringstream ss;

    
    return ss.str();
}