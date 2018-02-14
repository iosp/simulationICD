#ifndef INS_DATA_H
#define INS_DATA_H

/*
* DgpsData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::time_duration

class InsData {
private:
    boost::posix_time::time_duration m_simTime;
    boost::posix_time::time_duration m_utcTime;

    // members for INS navigation data message
    float m_altitude;
    float m_latitude;
    float m_longitude;
    float m_azimuth;
    float m_pitch;
    float m_roll;
    float m_azimuthRate;
    float m_northVelocity;
    float m_eastVelocity;
    float m_downVelocity;
    float m_distanceTraveled;
    float m_odometerDistance;
    bool m_motionDetected;
    // members for INS internal GPS
    short m_gpsFom;
    short m_numOfSatelites;
    // members for errors estimation message
    float m_horizontalError;
    float m_verticalError;
    float m_northingError;
    float m_eastingError;
    float m_altitudeError;
    float m_northVelocityError;
    float m_eastVelocityError;
    float m_downVelocityError;
    float m_azimuthErrorEstimation;
    float m_pitchErrorEstimation;
    float m_rollErrorEstimation;


public:
    InsData() = default;

    InsData(const boost::posix_time::time_duration& simTime);
    
    ~InsData() = default;

    const boost::posix_time::time_duration& GetSimTime() const {
        return m_simTime;
    }

    const boost::posix_time::time_duration& GetUtcTime() const {
        return m_utcTime;
    }

    float GetAltitude() const {
        return m_altitude;
    }

    float GetLatitude() const {
        return m_latitude;
    }

    float GetLongitude() const {
        return m_longitude;
    }

    float GetAzimuth() const {
        return m_azimuth;
    }

    float GetPitch() const {
        return m_pitch;
    }

    float GetRoll() const {
        return m_roll;
    }

    float GetAzimuthRate() const {
        return m_azimuthRate;
    }

    float GetNorthVelocity() const {
        return m_northVelocity;
    }

    float GetEastVelocity() const {
        return m_eastVelocity;
    }

    float GetDownVelocity() const {
        return m_downVelocity;
    }

    float GetDistanceTraveled() const {
        return m_distanceTraveled;
    }

    float GetOdometerDistance() const {
        return m_odometerDistance;
    }

    bool IsMotionDetected() const {
        return m_motionDetected;
    }

    int GetGpsFom() const {
        return m_gpsFom;
    }

    int GetNumOfSatelites() const {
        return m_numOfSatelites;
    }

    float GetHorizontalError() const {
        return m_horizontalError;
    }

    float GetVerticalError() const {
        return m_verticalError;
    }

    float GetNorthingError() const{
        return m_northingError;
    }

    float GetEastingError() const{
        return m_eastingError;
    }

    float GetAltitudeError() const{
        return m_altitudeError;
    }

    float GetNorthVelocityError() const {
        return m_northVelocityError;
    }

    float GetEastVelocityError() const {
        return m_eastVelocityError;
    }

    float GetDownVelocityError() const {
        return m_downVelocityError;
    }

    float GetAzimuthErrorEstimation() const {
        return m_azimuthErrorEstimation;
    }

    float GetPitchErrorEstimation() const {
        return m_pitchErrorEstimation;
    }

    float GetRollErrorEstimation() const {
        return m_rollErrorEstimation;
    }

    std::string toString() const;
};



#endif // INS_DATA_H