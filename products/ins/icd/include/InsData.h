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
    float m_altitude = 0;
    float m_latitude = 0;
    float m_longitude = 0;
    float m_azimuth = 0;
    float m_pitch = 0;
    float m_roll = 0;
    float m_azimuthRate = 0;
    float m_northVelocity = 0;
    float m_eastVelocity = 0;
    float m_downVelocity = 0;
    float m_distanceTraveled = 0;
    float m_odometerDistance = 0;
    bool m_motionDetected;
    // members for INS internal GPS
    short m_gpsFom = 0;
    short m_numOfSatelites = 0;
    // members for errors estimation message
    float m_horizontalError = 0;
    float m_verticalError = 0;
    float m_northingError = 0;
    float m_eastingError = 0;
    float m_altitudeError = 0;
    float m_northVelocityError = 0;
    float m_eastVelocityError = 0;
    float m_downVelocityError = 0;
    float m_azimuthErrorEstimation = 0;
    float m_pitchErrorEstimation = 0;
    float m_rollErrorEstimation = 0;


public:
    InsData() = default;
    
    ~InsData() = default;

    // InsData& operator = (const InsData& other);

    const boost::posix_time::time_duration& GetSimTime() const {
        return m_simTime;
    }

    void SetSimTime(const boost::posix_time::time_duration& simTime) {
        m_simTime = simTime;
    }

    const boost::posix_time::time_duration& GetUtcTime() const {
        return m_utcTime;
    }

    void SetUtcTime(const boost::posix_time::time_duration& utcTime) {
        m_utcTime = utcTime;
    }

    float GetAltitude() const {
        return m_altitude;
    }

    void SetAltitude(float altitude) {
        m_altitude = altitude;
    }

    float GetLatitude() const {
        return m_latitude;
    }

    void SetLatitude(float latitude) {
        m_latitude = latitude;
    }

    float GetLongitude() const {
        return m_longitude;
    }

    void SetLongitude(float longitude) {
        m_longitude = longitude;
    }

    float GetAzimuth() const {
        return m_azimuth;
    }

    void SetAzimuth(float azimuth) {
        m_azimuth = azimuth;
    }

    float GetPitch() const {
        return m_pitch;
    }

    void SetPitch(float pitch) {
        m_pitch = pitch;
    }
    
    float GetRoll() const {
        return m_roll;
    }

    void SetRoll(float roll) {
        m_roll = roll;
    }

    float GetAzimuthRate() const {
        return m_azimuthRate;
    }

    void SetAzimuthRate(float azimuthRate) {
        m_azimuthRate = azimuthRate;
    }

    float GetNorthVelocity() const {
        return m_northVelocity;
    }

    void SetNorthVelocity(float northVelocity) {
        m_northVelocity = northVelocity;
    }

    float GetEastVelocity() const {
        return m_eastVelocity;
    }

    void SetEastVelocity(float eastVelocity) {
        m_eastVelocity = eastVelocity;
    }

    float GetDownVelocity() const {
        return m_downVelocity;
    }

    void SetDownVelocity(float downVelocity) {
        m_downVelocity = downVelocity;
    }

    float GetDistanceTraveled() const {
        return m_distanceTraveled;
    }

    void SetDistanceTraveled(float distanceTraveled) {
        m_distanceTraveled = distanceTraveled;
    }

    float GetOdometerDistance() const {
        return m_odometerDistance;
    }

    void SetOdometerDistance(float odometerDistance) {
        m_odometerDistance = odometerDistance;
    }

    bool IsMotionDetected() const {
        return m_motionDetected;
    }

    void SetMotionDetected(float motionDetected) {
        m_motionDetected = motionDetected;
    }

    short GetGpsFom() const {
        return m_gpsFom;
    }

    void SetGpsFom(short gpsFom) {
        m_gpsFom = gpsFom;
    }

    short GetNumOfSatelites() const {
        return m_numOfSatelites;
    }

    void SetNumOfSatelites(short numOfSatelites) {
        m_numOfSatelites = numOfSatelites;
    }

    float GetHorizontalError() const {
        return m_horizontalError;
    }

    void SetHorizontalError(float horizontalError) {
        m_horizontalError = horizontalError;
    }

    float GetVerticalError() const {
        return m_verticalError;
    }

    void SetVerticalError(float verticalError) {
        m_verticalError = verticalError;
    }

    float GetNorthingError() const{
        return m_northingError;
    }

    void SetNorthingError(float northingError) {
        m_northingError = northingError;
    }

    float GetEastingError() const{
        return m_eastingError;
    }

    void SetEastingError(float eastingError) {
        m_eastingError = eastingError;
    }

    float GetAltitudeError() const{
        return m_altitudeError;
    }

    void SetAltitudeError(float altitudeError) {
        m_altitudeError = altitudeError;
    }

    float GetNorthVelocityError() const {
        return m_northVelocityError;
    }

    void SetNorthVelocityError(float northVelocityError) {
        m_northVelocityError = northVelocityError;
    }

    float GetEastVelocityError() const {
        return m_eastVelocityError;
    }

    void SetEastVelocityError(float eastVelocityError) {
        m_eastVelocityError = eastVelocityError;
    }

    float GetDownVelocityError() const {
        return m_downVelocityError;
    }

    void SetDownVelocityError(float downVelocityError) {
        m_downVelocityError = downVelocityError;
    }

    float GetAzimuthErrorEstimation() const {
        return m_azimuthErrorEstimation;
    }

    void SetAzimuthErrorEstimation(float azimuthErrorEstimation) {
        m_azimuthErrorEstimation = azimuthErrorEstimation;
    }

    float GetPitchErrorEstimation() const {
        return m_pitchErrorEstimation;
    }

    void SetPitchErrorEstimation(float pitchErrorEstimation) {
        m_pitchErrorEstimation = pitchErrorEstimation;
    }

    float GetRollErrorEstimation() const {
        return m_rollErrorEstimation;
    }

    void SetRollErrorEstimation(float rollErrorEstimation) {
        m_rollErrorEstimation = rollErrorEstimation;
    }

    std::string toString() const;
};



#endif // INS_DATA_H