#ifndef IPONWRAPPER_H
#define IPONWRAPPER_H

/*
* IponWrapper.h
* Wrapper for IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponData.h"
#include "IWrapper.h"

/**

 * */
class IponWrapper : public IWrapper<IponData> {
private:
    IponData m_data;

    /**
     * Clear current data of the object
     */ 
    void ClearCurrentData();

public:
    IponWrapper(const std::string& confFilePath);

    ~IponWrapper();

    /**
     * Calls ibeo->run
     */ 
    virtual void Run() override;

    /**
     * Take the temporary data and set it to icd
     */ 
    virtual void SetData() override;

    virtual void GetData() override {}

    void SetSimTime(float simTime);
    
    /************************************************* Periodic 1 HZ ********************************************/
    void Set1HZInsTime(double insTime);

    void Set1HZGpsTime(double gpsTime);

    void Set1HZLatitude(double latitude);

    void Set1HZLongitude(double longitude);

    void Set1HZAltitude(double altitude);

    void Set1HZWeek(short week);

    /************************************************* Periodic 100 HZ ********************************************/
    void Set100HZAzimuthGeo(double azimuthGeo);

    void Set100HZPitch(double pitch);

    void Set100HZRoll(double roll);

    void Set100HZRollRateX(double rollRateX);

    void Set100HZPitchRateY(double pitchRateY);

    void Set100HZAzimuthRateZ(double azimuthRateZ);

    void Set100HZEccX(double eccX);

    void Set100HZEccY(double eccY);

    void Set100HZEccZ(double eccZ) ;

    void Set100HZAltitude(double altitude);

    void Set100HZLatitude(double latitude);

    void Set100HZLongitude(double longitude);

    void Set100HZVelocityEast(double velocityEast);

    void Set100HZVelocityNorth(double velocityNorth);

    void Set100HZVelocityDown(double velocityDown);

    void Set100HZInsTimeOfNavData(double insTimeOfNavData);

};

#endif // IPONWRAPPER_H