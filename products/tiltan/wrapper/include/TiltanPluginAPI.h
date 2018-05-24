#ifndef TILTANPLUGINAPI_H
#define TILTANPLUGINAPI_H

/*
* TiltanPluginAPI.h
* API for external tools that need to use Tiltan
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

struct TiltanWrapper;

// Functions that can be used by the plugin
extern "C" {
    TiltanWrapper* TiltanCreateObject(const char* confFilePath);

    void TiltanDeleteObject(TiltanWrapper* pObj);

    void TiltanSendStatusMsgData(TiltanWrapper* pObj);

    void TiltanSendInternalGPSData(TiltanWrapper* pObj);

    void TiltanSendNavigationData(TiltanWrapper* pObj);

    void TiltanSendErrorEstimationData(TiltanWrapper* pObj);

    void TiltanSetTimeStamps(TiltanWrapper* pObj, float simTime, float utcTime);

    // Tiltan navigation data message
    void TiltanSetPose(TiltanWrapper* pObj, float latitude, float longitude, float altitude);

    void TiltanSetOrientation(TiltanWrapper* pObj, float azimuth, float pitch, float roll);

    void TiltanSetAzimuthRate(TiltanWrapper* pObj, float azimuthRate);

    void TiltanSetVelocity(TiltanWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity);

    void TiltanSetDistances(TiltanWrapper* pObj, float distanceTraveled, float odometerDistance);

    void TiltanSetMotionDetected(TiltanWrapper* pObj, bool motionDetected);

    // Tiltan internal GPS
    void TiltanSetInternalGpsFields(TiltanWrapper* pObj, short gpsFom, short numOfSatelites);

    // Tiltan Errors estimation message
    void TiltanSetDirectionErrors(TiltanWrapper* pObj, float horizontalError, float verticalError, float northingError,
                             float eastingError, float altitudeError);

    void TiltanSetVelocityErrors(TiltanWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError);

    void TiltanSetOrientationErrors(TiltanWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);
}

#endif // TILTANPLUGINAPI_H