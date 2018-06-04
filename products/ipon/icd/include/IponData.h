#ifndef IPON_DATA_H
#define IPON_DATA_H

/*
* IponData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 02.05.18
*/

#include <string>

enum IponMsgType : unsigned int {IPON_PERIODIC_1HZ, IPON_PERIODIC_100HZ }; 

class IponData {
private:

    struct PHSPeriodic_1HZ_Msg {
        double insTime = 0;
        double gpsTime = 0;
        double latitude = 0;
        double longitude = 0;
        double altitude = 0;
        short week = 0;
    } m_periodic1HZ;

    struct PHSPeriodic_100HZ_Msg {
        double azimuthGeo = 0;
        double pitch = 0;
        double roll = 0;
        double rollRateX = 0;
        double pitchRateY = 0;
        double azimuthRateZ = 0;
        double eccX = 0;
        double eccY = 0;
        double eccZ = 0;
        double altitude = 0;
        double latitude = 0;
        double longitude = 0;
        double velocityEast = 0;
        double velocityNorth = 0;
        double velocityDown = 0;
        double insTimeOfNavData = 0;
    } m_periodic100HZ;
    
    float m_simTime;

    IponMsgType m_currMsgType;

public:
    IponData() = default;
    
    ~IponData() = default;

    IponMsgType GetCurrMsgType() const {
        return m_currMsgType;
    }

    void SetCurrMsgType(IponMsgType msgType) {
        m_currMsgType = msgType;
    }

    /************************************************* Periodic 1 HZ ********************************************/
    double Get1HZInsTime() const {
        return m_periodic1HZ.insTime;
    }

    void Set1HZInsTime(double insTime) {
        m_periodic1HZ.insTime = insTime;
    }

    double Get1HZGpsTime() const {
        return m_periodic1HZ.gpsTime;
    }

    void Set1HZGpsTime(double gpsTime) {
        m_periodic1HZ.gpsTime = gpsTime;
    }

    double Get1HZLatitude() const {
        return m_periodic1HZ.latitude;
    }

    void Set1HZLatitude(double latitude) {
        m_periodic1HZ.latitude = latitude;
    }

    double Get1HZLongitude() const {
        return m_periodic1HZ.longitude;
    }

    void Set1HZLongitude(double longitude) {
        m_periodic1HZ.longitude = longitude;
    }

    double Get1HZAltitude() const {
        return m_periodic1HZ.altitude;
    }

    void Set1HZAltitude(double altitude) {
        m_periodic1HZ.altitude = altitude;
    }

    short Get1HZWeek() const {
        return m_periodic1HZ.week;
    }

    void Set1HZWeek(short week) {
        m_periodic1HZ.week = week;
    }

    /************************************************* Periodic 100 HZ ********************************************/
    double Get100HZAzimuthGeo() const {
        return m_periodic100HZ.azimuthGeo;
    }

    void Set100HZAzimuthGeo(double azimuthGeo) {
        m_periodic100HZ.azimuthGeo = azimuthGeo;
    }

    double Get100HZPitch() const {
        return m_periodic100HZ.pitch;
    }

    void Set100HZPitch(double pitch) {
        m_periodic100HZ.pitch = pitch;
    }

    double Get100HZRoll() const {
        return m_periodic100HZ.roll;
    }

    void Set100HZRoll(double roll) {
        m_periodic100HZ.roll = roll;
    }

    double Get100HZRollRateX() const {
        return m_periodic100HZ.rollRateX;
    }

    void Set100HZRollRateX(double rollRateX) {
        m_periodic100HZ.rollRateX = rollRateX;
    }

    double Get100HZPitchRateY() const {
        return m_periodic100HZ.pitchRateY;
    }

    void Set100HZPitchRateY(double pitchRateY) {
        m_periodic100HZ.pitchRateY = pitchRateY;
    }

    double Get100HZAzimuthRateZ() const {
        return m_periodic100HZ.azimuthRateZ;
    }

    void Set100HZAzimuthRateZ(double azimuthRateZ) {
        m_periodic100HZ.azimuthRateZ = azimuthRateZ;
    }

    double Get100HZEccX() const {
        return m_periodic100HZ.eccX;
    }

    void Set100HZEccX(double eccX) {
        m_periodic100HZ.eccX = eccX;
    }

    double Get100HZEccY() const {
        return m_periodic100HZ.eccY;
    }

    void Set100HZEccY(double eccY) {
        m_periodic100HZ.eccY = eccY;
    }

    double Get100HZEccZ() const {
        return m_periodic100HZ.eccZ;
    }

    void Set100HZEccZ(double eccZ) {
        m_periodic100HZ.eccZ = eccZ;
    }

    double Get100HZAltitude() const {
        return m_periodic100HZ.altitude;
    }

    void Set100HZAltitude(double altitude) {
        m_periodic100HZ.altitude = altitude;
    }

    double Get100HZLatitude() const {
        return m_periodic100HZ.latitude;
    }

    void Set100HZLatitude(double latitude) {
        m_periodic100HZ.latitude = latitude;
    }

    double Get100HZLongitude() const {
        return m_periodic100HZ.longitude;
    }

    void Set100HZLongitude(double longitude) {
        m_periodic100HZ.longitude = longitude;
    }

    double Get100HZVelocityEast() const {
        return m_periodic100HZ.velocityEast;
    }

    void Set100HZVelocityEast(double velocityEast) {
        m_periodic100HZ.velocityEast = velocityEast;
    }

    double Get100HZVelocityNorth() const {
        return m_periodic100HZ.velocityNorth;
    }

    void Set100HZVelocityNorth(double velocityNorth) {
        m_periodic100HZ.velocityNorth = velocityNorth;
    }

    double Get100HVelocityDown() const {
        return m_periodic100HZ.velocityDown;
    }

    void Set100HZVelocityDown(double velocityDown) {
        m_periodic100HZ.velocityDown = velocityDown;
    }

    double Get100HZInsTimeOfNavData() const {
        return m_periodic100HZ.insTimeOfNavData;
    }

    void Set100HZInsTimeOfNavData(double insTimeOfNavData) {
        m_periodic100HZ.insTimeOfNavData = insTimeOfNavData;
    }


    float GetSimTime() const {
        return m_simTime;
    }

    void SetSimTime(float simTime) {
        m_simTime = simTime;
    }

    std::string toString(IponMsgType msgType) const;
};



#endif // IPON_DATA_H