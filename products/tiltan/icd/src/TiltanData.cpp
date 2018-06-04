/*
* TiltanData.cpp
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 12.02.18
* 
*/

#include "TiltanData.h"
#include <sstream>

std::string TiltanData::toString(TiltanMsgType msgType) const {
    std::stringstream ss;
    ss << std::endl;

    switch (msgType) {
        case TILTAN_STATUS_MSG:
             ss << "***** Status message *****" << std::endl;
             break;
        case TILTAN_NAVIGATION_DATA_MSG:
            ss << "***** Navigation data message *****" << std::endl << "     " <<
                "Altitude: " << m_navigationData.altitude << ". Latitude: " <<  m_navigationData.latitude << 
                ". Longitude: " << m_navigationData.longitude << ". Azimuth: " << m_navigationData.azimuth <<
                ". Pitch: " << m_navigationData.pitch << ". Roll: " << m_navigationData.roll << 
                ". Azimuth Rate: " << m_navigationData.azimuthRate << ". North Velocity: " << m_navigationData.northVelocity <<
                ". East Velocity: " << m_navigationData.eastVelocity << ". Down Velocity: " << m_navigationData.downVelocity << 
                ". Distance Traveled: " << m_navigationData.distanceTraveled << 
                ". Odometer distance: " << m_navigationData.odometerDistance << ". Motion detected: " << m_navigationData.motionDetected << std::endl;
            break;
        case TILTAN_INTERNAL_GPS_MSG:
            ss << "***** Tiltan internal GPS message *****" << std::endl << "     " <<
                "GPS FOM: " << m_internalGPS.gpsFom << ". Num of satelites: " << m_internalGPS.numOfSatelites << std::endl;
            break;
        case TILTAN_ERRORS_ESTIMATION_MSG:
            ss << "***** Errors estimation message ***** " << std::endl << "     " <<
                "Horizontal error: " << m_errorsEstimation.horizontalError << ". Vertical error: " << m_errorsEstimation.verticalError << 
                ". Northing error: " << m_errorsEstimation.northingError <<  ". Easting error: " << m_errorsEstimation.eastingError <<
                 ". Altitude error: " << m_errorsEstimation.altitudeError << ". North velocity error: " << m_errorsEstimation.northVelocityError <<
                ". East velocity error: " << m_errorsEstimation.eastVelocityError << ". Down velocity error: " << m_errorsEstimation.downVelocityError <<
                ". Azimuth error estimation: " << m_errorsEstimation.azimuthErrorEstimation << 
                ". Pitch error estimation: " << m_errorsEstimation.pitchErrorEstimation <<
                ". Roll error estimation: " << m_errorsEstimation.rollErrorEstimation << std::endl;
            break;
        default:
            break;

    }

    ss << "Simulation time: " << m_simTime << ". UTC time: " << m_utcTime << std::endl;
    
    return ss.str();
}