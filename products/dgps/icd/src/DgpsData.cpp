/*
* DgpsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
* 
*/

#include "DgpsData.h"

DgpsData::DgpsData(double latitude, double longitude, double altitude, 
    double horizontalSpeed, double verticalSpeed, double velocityAzimuth, const boost::posix_time::time_duration& simTime) :
    m_latitude(latitude), m_longitude(longitude), m_altitude(altitude), m_horizontalSpeed(horizontalSpeed), m_verticalSpeed(verticalSpeed),
    m_velocityAzimuth(velocityAzimuth), m_simTime(simTime){
    
}