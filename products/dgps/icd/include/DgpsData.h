#ifndef DGPS_DATA_H
#define DGPS_DATA_H

/*
* DgpsData.h
* Represents the data that is passed between the ICD and the user of the lib
* Author: Binyamin Appelbaum
* Date: 15.01.18
* 
*/

#include <boost/date_time/posix_time/posix_time.hpp> // boost::posix_time::time_duration

class DgpsData {
private:
    double m_latitude;
    double m_longitude;
    double m_altitude;
    double m_horizontalSpeed; // horizontal speed over ground, in meters per second
    double m_verticalSpeed; // Veritical speed , meters per seconds
	double m_velocityAzimuth; // Actual direction of motion over ground with respect to True North, deg
    boost::posix_time::time_duration m_simTime;

public:
    DgpsData() = default;

    DgpsData(double latitude, double longitude, double altitude, 
                double horizontalSpeed, double verticalSpeed, double velocityAzimuth, const boost::posix_time::time_duration& simTime);
    
    ~DgpsData() = default;

    double GetLatitude() const {
        return m_latitude;
    }

    double GetLongitude() const {
        return m_longitude;
    }

    double GetAltitude() const {
        return m_altitude;
    }

    double GetHorizontalSpeed() const {
        return m_horizontalSpeed;
    }

    double GetVerticalSpeed() const {
        return m_verticalSpeed;
    }

    double GetVelocityAzimuth() const {
        return m_velocityAzimuth;
    }

    const boost::posix_time::time_duration& GetSimTime() const {
        return m_simTime;
    }
};



#endif // DGPS_DATA_H