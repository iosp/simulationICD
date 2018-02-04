/*
* DgpsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
* 
*/

#include "DgpsData.h"

DgpsData::DgpsData(double latitude, double longitude, double altitude, 
                double latSpeed, double longSpeed, double altAzimuth, const boost::posix_time::time_duration& simTime) :
    m_latitude(latitude), m_longitude(longitude), m_altitude(altitude), m_latSpeed(latSpeed), m_longSpeed(longSpeed),
    m_altAzimuth(altAzimuth), m_simTime(simTime){
    
}