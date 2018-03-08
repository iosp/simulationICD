#ifndef INSPLUGINAPI_H
#define INSPLUGINAPI_H

/*
* InsPluginAPI.h
* API for external tools that need to use INS
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "InsWrapper.h"

// Functions that can be used by the plugin
extern "C" {
    InsWrapper* CreateInsObject(const char* confFilePath);

    void DeleteInsObject(InsWrapper* pObj);

    void RunIns(InsWrapper* pObj);

    void SendInsData(InsWrapper* pObj);

    void SetInsTimeStamps(InsWrapper* pObj, float simTime, float utcTime);

    // INS navigation data message
    void SetInsPose(InsWrapper* pObj, float latitude, float longitude, float altitude);

    void SetInsOrientation(InsWrapper* pObj, float azimuth, float pitch, float roll);

    void SetInsAzimuthRate(InsWrapper* pObj, float azimuthRate);

    void SetInsVelocity(InsWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity);

    void SetInsDistances(InsWrapper* pObj, float distanceTraveled, float odometerDistance);

    void SetInsMotionDetected(InsWrapper* pObj, bool motionDetected);

    // INS internal GPS
    void SetInsInternalGpsFields(InsWrapper* pObj, short gpsFom, short numOfSatelites);

    // INS Errors estimation message
    void SetInsDirectionErrors(InsWrapper* pObj, float horizontalError, float verticalError, float northingError,
                             float eastingError, float altitudeError);

    void SetInsVelocityErrors(InsWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError);

    void SetInsOrientationErrors(InsWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation);

}

#endif // INSPLUGINAPI_H