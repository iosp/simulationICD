/*
* DgpsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
* 
*/

#include "DgpsData.h"
#include <sstream>

DgpsData::DgpsData(double latitude, double longitude, double altitude, 
                double latSpeed, double longSpeed, double altAzimuth, const boost::posix_time::time_duration& simTime) :
    m_latitude(latitude), m_longitude(longitude), m_altitude(altitude), m_latSpeed(latSpeed), m_longSpeed(longSpeed),
    m_altAzimuth(altAzimuth), m_simTime(simTime){
    
}

std::string DgpsData::toString() const {
    std::stringstream ss;
    ss << "Latitude: " << m_latitude << ". Longitude: " << m_longitude << ". Altitude: " << m_altitude << std::endl <<
        "Lat speed: " << m_latSpeed << ". Long speed: " << m_longSpeed << ". Alt Azimuth: " << m_altAzimuth << std::endl <<
        "Simulation time: " << m_simTime;
    
    return ss.str();
}