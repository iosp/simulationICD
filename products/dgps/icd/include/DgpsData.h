#ifndef DGPS_DATA_H
#define DGPS_DATA_H

/*
* DgpsData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
*/

#include <string>

enum DgpsMsgType {DGPS_BEST_POS, DGPS_BEST_VEL };

class DgpsData {
private:
    struct Best_Pos {
        double latitude;
        double longitude;
        double altitude;
    } m_bestPos;

    struct Best_Vel {
        double latitude; // horizontal speed over ground, in meters per second
        double longitude; // Veritical speed , meters per seconds
	    double altitude; // Actual direction of motion over ground with respect to True North, deg
    } m_bestVel;

    float m_simTime;

    DgpsMsgType m_currMsgType;

public:
    DgpsData() = default;
    
    ~DgpsData() = default;

    double GetBestPosLatitude() const {
        return m_bestPos.latitude;
    }

    void SetBestPosLatitude(double latitude) {
        m_bestPos.latitude = latitude;
    }

    double GetBestPosLongitude() const {
        return m_bestPos.longitude;
    }

    void SetBestPosLongitude(double longitude) {
        m_bestPos.longitude = longitude;
    }

    double GetBestPosAltitude() const {
        return m_bestPos.altitude;
    }

    void SetBestPosAltitude(double altitude) {
        m_bestPos.altitude = altitude;
    }

    double GetBestVelLatitude() const {
        return m_bestVel.latitude;
    }

    void SetBestVelLatitude(double latitude) {
        m_bestVel.latitude = latitude;
    }

    double GetBestVelLongitude() const {
        return m_bestVel.longitude;
    }

    void SetBestVelLongitude(double longitude) {
        m_bestVel.longitude = longitude;
    }

    double GetBestVelAltitude() const {
        return m_bestVel.altitude;
    }
    
    void SetBestVelAltitude(double altitude) {
        m_bestVel.altitude = altitude;
    }

    DgpsMsgType GetCurrMsgType() const {
        return m_currMsgType;
    }

    void SetCurrMsgType(DgpsMsgType msgType) {
        m_currMsgType = msgType;
    }

    float GetSimTime() const {
        return m_simTime;
    }

    void SetSimTime(float simTime){
        m_simTime = simTime;
    }

    std::string toString(DgpsMsgType msgType) const;
};



#endif // DGPS_DATA_H