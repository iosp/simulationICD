#ifndef IPONPLUGINAPI_H
#define IPONPLUGINAPI_H

/*
* IponPluginAPI.h
* API for external tools that need to use IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

struct IponWrapper;

// Functions that can be used by the plugin
extern "C" {
    IponWrapper* IponCreateObject(const char* confFilePath);

    void IponDeleteObject(IponWrapper* pObj);

    void IponSendPeriodic1HZData(IponWrapper* pObj);

    void IponSendPeriodic100HZData(IponWrapper* pObj);

    void IponSetSimTime(IponWrapper* pObj, float simTime);

    /************************************************* Periodic 1 HZ ********************************************/
    void IponSet1HZInsTime(IponWrapper* pObj, double insTime);

    void IponSet1HZGpsTime(IponWrapper* pObj, double gpsTime);

    void IponSet1HZLatitude(IponWrapper* pObj, double latitude);

    void IponSet1HZLongitude(IponWrapper* pObj, double longitude);

    void IponSet1HZAltitude(IponWrapper* pObj, double altitude);

    void IponSet1HZWeek(IponWrapper* pObj, short week);

    /************************************************* Periodic 100 HZ ********************************************/
    void IponSet100HZAzimuthGeo(IponWrapper* pObj, double azimuthGeo);

    void IponSet100HZPitch(IponWrapper* pObj, double pitch);

    void IponSet100HZRoll(IponWrapper* pObj, double roll);

    void IponSet100HZRollRateX(IponWrapper* pObj, double rollRateX);

    void IponSet100HZPitchRateY(IponWrapper* pObj, double pitchRateY);

    void IponSet100HZAzimuthRateZ(IponWrapper* pObj, double azimuthRateZ);

    void IponSet100HZEccX(IponWrapper* pObj, double eccX);

    void IponSet100HZEccY(IponWrapper* pObj, double eccY);

    void IponSet100HZAltitude(IponWrapper* pObj, double altitude);

    void IponSet100HZLatitude(IponWrapper* pObj, double latitude);

    void IponSet100HZLongitude(IponWrapper* pObj, double longitude);

    void IponSet100HZVelocityEast(IponWrapper* pObj, double velocityEast);

    void IponSet100HZVelocityNorth(IponWrapper* pObj, double velocityNorth);

    void IponSet100HZVelocityDown(IponWrapper* pObj, double velocityDown);

    void IponSet100HZInsTimeOfNavData(IponWrapper* pObj, double insTimeOfNavData);
}

#endif // IPONPLUGINAPI_H