/*
* InsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "InsData.h"
#include <sstream>

std::string InsData::toString(const std::bitset<8>& message) const {
    std::stringstream ss;
    ss << std::endl;

    if ((message & INS_STATUS_BIT).any()) {
        ss << "***** Status message *****" << std::endl;
    }
    if ((message & INS_NAV_BIT).any()) {
        ss << "***** Navigation data message *****" << std::endl << "     " <<
            "Altitude: " << m_altitude << ". Latitude: " <<  m_latitude << ". Longitude: " << m_longitude << ". Azimuth: " << m_azimuth <<
            ". Pitch: " << m_pitch << ". Roll: " << m_roll << ". Azimuth Rate: " << m_azimuthRate << ". North Velocity: " << m_northVelocity <<
            ". East Velocity: " << m_eastVelocity << ". Down Velocity: " << m_downVelocity << ". Distance Traveled: " << m_distanceTraveled << 
            ". Odometer distance: " << m_odometerDistance << ". Motion detected: " << m_motionDetected << std::endl;
    }
    if ((message & INS_INTERNAL_BIT).any()) {    
        ss << "***** INS internal GPS message *****" << std::endl << "     " <<
            "GPS FOM: " << m_gpsFom << ". Num of satelites: " << m_numOfSatelites << std::endl;
    }
    if ((message & INS_ERR_EST_BIT).any()) {
        ss << "***** Errors estimation message ***** " << std::endl << "     " <<
            "Horizontal error: " << m_horizontalError << ". Vertical error: " << m_verticalError << ". Northing error: " << m_northingError << 
            ". Easting error: " << m_eastingError << ". Altitude error: " << m_altitudeError << ". North velocity error: " << m_northVelocityError <<
            ". East velocity error: " << m_eastVelocityError << ". Down velocity error: " << m_downVelocityError <<
            ". Azimuth error estimation: " << m_azimuthErrorEstimation <<  ". Pitch error estimation: " << m_pitchErrorEstimation <<
            ". Roll error estimation: " << m_rollErrorEstimation << std::endl;
    }

    ss << "simulation time: " << m_simTime << " . UTC time: " << m_utcTime << std::endl;
    
    return ss.str();
}