#ifndef INSPLUGINAPI_H
#define INSPLUGINAPI_H

/*
* InsPluginAPI.h
* API for external tools that need to use INS
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

struct InsWrapper;

// Functions that can be used by the plugin
extern "C" {
    InsWrapper* InsCreateObject(const char* confFilePath);

    void InsDeleteObject(InsWrapper* pObj);

    void InsSendStatusMsgData(InsWrapper* pObj);

    void InsSendInternalGPSData(InsWrapper* pObj);

    void InsSendNavigationData(InsWrapper* pObj);

    void InsSendErrorEstimationData(InsWrapper* pObj);

    void InsSetTimeStamps(InsWrapper* pObj, float simTime, float utcTime);

    // INS navigation data message
    void InsSetPose(InsWrapper* pObj, float latitude, float longitude, float altitude);

    void InsSetOrientation(InsWrapper* pObj, float azimuth, float pitch, float roll);

    void InsSetAzimuthRate(InsWrapper* pObj, float azimuthRate);

    void InsSetVelocity(InsWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity);

    void InsSetDistances(InsWrapper* pObj, float distanceTraveled, float odometerDistance);

    void InsSetMotionDetected(InsWrapper* pObj, bool motionDetected);

    // INS internal GPS
    void InsSetInternalGpsFields(InsWrapper* pObj, short gpsFom, short numOfSatelites);

    // INS Errors estimation message
    void InsSetDirectionErrors(InsWrapper* pObj, float horizontalError, float verticalError, float northingError,
                             float eastingError, float altitudeError);

    void InsSetVelocityErrors(InsWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError);

    void InsSetOrientationErrors(InsWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);
}

#endif // INSPLUGINAPI_H