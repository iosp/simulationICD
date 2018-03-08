#ifndef DGPS_DATA_H
#define DGPS_DATA_H

/*
* DgpsData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include <string>

class DgpsData {
private:
    double m_latitude;
    double m_longitude;
    double m_altitude;
    double m_latSpeed; // horizontal speed over ground, in meters per second
    double m_longSpeed; // Veritical speed , meters per seconds
	double m_altAzimuth; // Actual direction of motion over ground with respect to True North, deg
    float m_simTime;

public:
    DgpsData() = default;
    
    ~DgpsData() = default;

    double GetLatitude() const {
        return m_latitude;
    }

    void SetLatitude(double latitude) {
        m_latitude = latitude;
    }

    double GetLongitude() const {
        return m_longitude;
    }

    void SetLongitude(double longitude) {
        m_longitude = longitude;
    }

    double GetAltitude() const {
        return m_altitude;
    }

    void SetAltitude(double altitude) {
        m_altitude = altitude;
    }

    double GetLatSpeed() const {
        return m_latSpeed;
    }

    void SetLatSpeed(double latSpeed) {
        m_latSpeed = latSpeed;
    }

    double GetLongSpeed() const {
        return m_longSpeed;
    }

    void SetLongSpeed(double longSpeed) {
        m_longSpeed = longSpeed;
    }

    double GetAltAzimuth() const {
        return m_altAzimuth;
    }
    
    void SetAltAzimuth(double altAzimuth) {
        m_altAzimuth = altAzimuth;
    }

    float GetSimTime() const {
        return m_simTime;
    }

    void SetSimTime(float simTime){
        m_simTime = simTime;
    }

    std::string toString() const;
};



#endif // DGPS_DATA_H