#ifndef INS_DATA_H
#define INS_DATA_H

/*
* DgpsData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 11.02.18
*/

#include <string>

enum InsMsgType : unsigned int {INS_STATUS_MSG, INS_NAVIGATION_DATA_MSG, INS_INTERNAL_GPS_MSG, INS_ERRORS_ESTIMATION_MSG }; 

class InsData {
private:
    InsMsgType m_currMsgType;
    float m_simTime;
    float m_utcTime;

    // members for INS navigation data message
    struct Ins_Navigation_Data {
        float altitude = 0;
        float latitude = 0;
        float longitude = 0;
        float azimuth = 0;
        float pitch = 0;
        float roll = 0;
        float azimuthRate = 0;
        float northVelocity = 0;
        float eastVelocity = 0;
        float downVelocity = 0;
        float distanceTraveled = 0;
        float odometerDistance = 0;
        bool motionDetected;
    } m_navigationData;
    // members for INS internal GPS
    struct Ins_Internal_GPS {
        short gpsFom = 0;
        short numOfSatelites = 0;
    } m_internalGPS;
    // members for errors estimation message
    struct Ins_Errors_Estimation {
        float horizontalError = 0;
        float verticalError = 0;
        float northingError = 0;
        float eastingError = 0;
        float altitudeError = 0;
        float northVelocityError = 0;
        float eastVelocityError = 0;
        float downVelocityError = 0;
        float azimuthErrorEstimation = 0;
        float pitchErrorEstimation = 0;
        float rollErrorEstimation = 0;
    } m_errorsEstimation;

public:
    InsData() = default;
    
    ~InsData() = default;

    InsMsgType GetCurrMsgType() const {
        return m_currMsgType;
    }

    void SetCurrMsgType(InsMsgType msgType) {
        m_currMsgType = msgType;
    }

    float GetSimTime() const {
        return m_simTime;
    }

    void SetSimTime(float simTime) {
        m_simTime = simTime;
    }

    float GetUtcTime() const {
        return m_utcTime;
    }

    void SetUtcTime(float utcTime) {
        m_utcTime = utcTime;
    }

    float GetInsNavAltitude() const {
        return m_navigationData.altitude;
    }

    void SetNavDataAltitude(float altitude) {
        m_navigationData.altitude = altitude;
    }

    float GetNavDataLatitude() const {
        return m_navigationData.latitude;
    }

    void SetNavDataLatitude(float latitude) {
        m_navigationData.latitude = latitude;
    }

    float GetNavDataLongitude() const {
        return m_navigationData.longitude;
    }

    void SetNavDataLongitude(float longitude) {
        m_navigationData.longitude = longitude;
    }

    float GetNavDataAzimuth() const {
        return m_navigationData.azimuth;
    }

    void SetNavDataAzimuth(float azimuth) {
        m_navigationData.azimuth = azimuth;
    }

    float GetNavDataPitch() const {
        return m_navigationData.pitch;
    }

    void SetNavDataPitch(float pitch) {
        m_navigationData.pitch = pitch;
    }
    
    float GetNavDataRoll() const {
        return m_navigationData.roll;
    }

    void SetNavDataRoll(float roll) {
        m_navigationData.roll = roll;
    }

    float GetNavDataAzimuthRate() const {
        return m_navigationData.azimuthRate;
    }

    void SetNavDataAzimuthRate(float azimuthRate) {
        m_navigationData.azimuthRate = azimuthRate;
    }

    float GetNavDataNorthVelocity() const {
        return m_navigationData.northVelocity;
    }

    void SetNavDataNorthVelocity(float northVelocity) {
        m_navigationData.northVelocity = northVelocity;
    }

    float GetNavDataEastVelocity() const {
        return m_navigationData.eastVelocity;
    }

    void SetNavDataEastVelocity(float eastVelocity) {
        m_navigationData.eastVelocity = eastVelocity;
    }

    float GetNavDataDownVelocity() const {
        return m_navigationData.downVelocity;
    }

    void SetNavDataDownVelocity(float downVelocity) {
        m_navigationData.downVelocity = downVelocity;
    }

    float GetNavDataDistanceTraveled() const {
        return m_navigationData.distanceTraveled;
    }

    void SetNavDataDistanceTraveled(float distanceTraveled) {
        m_navigationData.distanceTraveled = distanceTraveled;
    }

    float GetNavDataOdometerDistance() const {
        return m_navigationData.odometerDistance;
    }

    void SetNavDataOdometerDistance(float odometerDistance) {
        m_navigationData.odometerDistance = odometerDistance;
    }

    bool IsNavDataMotionDetected() const {
        return m_navigationData.motionDetected;
    }

    void SetNavDataMotionDetected(float motionDetected) {
        m_navigationData.motionDetected = motionDetected;
    }

    short GetIntGpsGpsFom() const {
        return m_internalGPS.gpsFom;
    }

    void SetIntGpsGpsFom(short gpsFom) {
        m_internalGPS.gpsFom = gpsFom;
    }

    short GetIntGpsNumOfSatelites() const {
        return m_internalGPS.numOfSatelites;
    }

    void SetIntGpsNumOfSatelites(short numOfSatelites) {
        m_internalGPS.numOfSatelites = numOfSatelites;
    }

    float GetHorizontalError() const {
        return m_errorsEstimation.horizontalError;
    }

    void SetHorizontalError(float horizontalError) {
        m_errorsEstimation.horizontalError = horizontalError;
    }

    float GetVerticalError() const {
        return m_errorsEstimation.verticalError;
    }

    void SetVerticalError(float verticalError) {
        m_errorsEstimation.verticalError = verticalError;
    }

    float GetNorthingError() const{
        return m_errorsEstimation.northingError;
    }

    void SetNorthingError(float northingError) {
        m_errorsEstimation.northingError = northingError;
    }

    float GetEastingError() const{
        return m_errorsEstimation.eastingError;
    }

    void SetEastingError(float eastingError) {
        m_errorsEstimation.eastingError = eastingError;
    }

    float GetAltitudeError() const{
        return m_errorsEstimation.altitudeError;
    }

    void SetAltitudeError(float altitudeError) {
        m_errorsEstimation.altitudeError = altitudeError;
    }

    float GetNorthVelocityError() const {
        return m_errorsEstimation.northVelocityError;
    }

    void SetNorthVelocityError(float northVelocityError) {
        m_errorsEstimation.northVelocityError = northVelocityError;
    }

    float GetEastVelocityError() const {
        return m_errorsEstimation.eastVelocityError;
    }

    void SetEastVelocityError(float eastVelocityError) {
        m_errorsEstimation.eastVelocityError = eastVelocityError;
    }

    float GetDownVelocityError() const {
        return m_errorsEstimation.downVelocityError;
    }

    void SetDownVelocityError(float downVelocityError) {
        m_errorsEstimation.downVelocityError = downVelocityError;
    }

    float GetAzimuthErrorEstimation() const {
        return m_errorsEstimation.azimuthErrorEstimation;
    }

    void SetAzimuthErrorEstimation(float azimuthErrorEstimation) {
        m_errorsEstimation.azimuthErrorEstimation = azimuthErrorEstimation;
    }

    float GetPitchErrorEstimation() const {
        return m_errorsEstimation.pitchErrorEstimation;
    }

    void SetPitchErrorEstimation(float pitchErrorEstimation) {
        m_errorsEstimation.pitchErrorEstimation = pitchErrorEstimation;
    }

    float GetRollErrorEstimation() const {
        return m_errorsEstimation.rollErrorEstimation;
    }

    void SetRollErrorEstimation(float rollErrorEstimation) {
        m_errorsEstimation.rollErrorEstimation = rollErrorEstimation;
    }

    std::string toString(InsMsgType msgType) const;
};



#endif // INS_DATA_H