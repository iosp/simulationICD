/*
* DgpsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
* 
*/

#include "DgpsData.h"
#include <sstream>

std::string DgpsData::toString(DgpsMsgType msgType) const {
    std::stringstream ss;
    ss << std::endl;
    switch (msgType) {
        case DGPS_BEST_POS:
          ss << "***** Best Pos *****" << std::endl <<
            "Latitude: " << m_bestPos.latitude << ". Longitude: " << m_bestPos.longitude << ". Altitude: " << m_bestPos.altitude << std::endl;
            break;
        case DGPS_BEST_VEL:
            ss << "***** Best Vel *****" << std::endl <<
                "Latitude: " << m_bestVel.latitude << ". Longitude: " << m_bestVel.longitude << ". Altitude: " << m_bestVel.altitude << std::endl;
            break;
        default:
            break;
    } 
    ss << "Simulation time: " << m_simTime;
    
    return ss.str();
}