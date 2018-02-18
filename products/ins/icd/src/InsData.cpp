/*
* InsData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "InsData.h"
#include <sstream>

#define ASSIGN_IF_NOT_ZERO(val, def) (val != 0 ? val : def) 

InsData::InsData(const boost::posix_time::time_duration& simTime) : m_simTime(simTime){
    
}

InsData& InsData::operator = (const InsData& other) {
    if (this != &other) {
        m_simTime = other.m_simTime;
        m_utcTime = other.m_utcTime;
        m_altitude = ASSIGN_IF_NOT_ZERO(other.m_altitude, m_altitude);
        m_latitude = ASSIGN_IF_NOT_ZERO(other.m_latitude, m_latitude);
        m_longitude = ASSIGN_IF_NOT_ZERO(other.m_longitude, m_longitude);
        m_azimuth = ASSIGN_IF_NOT_ZERO(other.m_azimuth, m_azimuth);
        m_pitch = ASSIGN_IF_NOT_ZERO(other.m_pitch, m_pitch);
        m_roll = ASSIGN_IF_NOT_ZERO(other.m_roll, m_roll);
        m_azimuthRate = ASSIGN_IF_NOT_ZERO(other.m_azimuthRate, m_azimuthRate);
        m_northVelocity = ASSIGN_IF_NOT_ZERO(other.m_northVelocity, m_northVelocity);
        m_eastVelocity = ASSIGN_IF_NOT_ZERO(other.m_eastVelocity, m_eastVelocity);
        m_downVelocity = ASSIGN_IF_NOT_ZERO(other.m_downVelocity, m_downVelocity);
        m_distanceTraveled = ASSIGN_IF_NOT_ZERO(other.m_distanceTraveled, m_distanceTraveled);
        m_odometerDistance = ASSIGN_IF_NOT_ZERO(other.m_odometerDistance, m_odometerDistance);
        m_motionDetected = ASSIGN_IF_NOT_ZERO(other.m_motionDetected, m_motionDetected);
        
        m_gpsFom = ASSIGN_IF_NOT_ZERO(other.m_gpsFom, m_gpsFom);
        m_numOfSatelites = ASSIGN_IF_NOT_ZERO(other.m_numOfSatelites, m_numOfSatelites);

        m_horizontalError = ASSIGN_IF_NOT_ZERO(other.m_horizontalError, m_horizontalError);
        m_verticalError = ASSIGN_IF_NOT_ZERO(other.m_verticalError, m_verticalError);
        m_northingError = ASSIGN_IF_NOT_ZERO(other.m_northingError, m_northingError);
        m_eastingError = ASSIGN_IF_NOT_ZERO(other.m_eastingError, m_eastingError);
        m_altitudeError = ASSIGN_IF_NOT_ZERO(other.m_altitudeError, m_altitudeError);
        m_northVelocityError = ASSIGN_IF_NOT_ZERO(other.m_northVelocityError, m_northVelocityError);
        m_eastVelocityError = ASSIGN_IF_NOT_ZERO(other.m_eastVelocityError, m_eastVelocityError);
        m_downVelocityError = ASSIGN_IF_NOT_ZERO(other.m_downVelocityError, m_downVelocityError);
        m_azimuthErrorEstimation = ASSIGN_IF_NOT_ZERO(other.m_azimuthErrorEstimation, m_azimuthErrorEstimation);
        m_pitchErrorEstimation = ASSIGN_IF_NOT_ZERO(other.m_pitchErrorEstimation, m_pitchErrorEstimation);
        m_rollErrorEstimation = ASSIGN_IF_NOT_ZERO(other.m_rollErrorEstimation, m_rollErrorEstimation);
    }
    return *this;

}

std::string InsData::toString() const {
    std::stringstream ss;
    ss << "Navigation data message: " << std::endl << "     " <<
        "Altitude: " << m_altitude << ". Latitude: " <<  m_latitude << ". Longitude: " << m_longitude << ". Azimuth: " << m_azimuth <<
        ". Pitch: " << m_pitch << ". Roll: " << m_roll << ". Azimuth Rate: " << m_azimuthRate << ". North Velocity: " << m_northVelocity <<
        ". East Velocity: " << m_eastVelocity << ". Dowm Velocity: " << m_downVelocity << ". Distance Traveled: " << m_distanceTraveled << 
        ". Odometer distance: " << m_odometerDistance << ". Motion detected: " << m_motionDetected << std::endl;
    
    ss << "INS internal GPS message: " << std::endl << "     " <<
        "GPS FOM: " << m_gpsFom << ". Num of satelites: " << m_numOfSatelites << std::endl;
    
    ss << "Errors estimation message: " << std::endl << "     " <<
        "Horizontal error: " << m_horizontalError << ". Vertical error: " << m_verticalError << ". Northing error: " << m_northingError << 
        ". Easting error: " << m_eastingError << ". Altitude error: " << m_altitudeError << ". North velocity error: " << m_northVelocityError <<
        ". East velocity error: " << m_eastVelocityError << ". Down velocity error: " << m_downVelocityError <<
        ". Azimuth error estimation: " << m_azimuthErrorEstimation <<  ". Pitch error estimation: " << m_pitchErrorEstimation <<
        ". Roll error estimation: " << m_rollErrorEstimation << std::endl;
    
    return ss.str();
}