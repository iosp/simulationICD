

/*
* InsPluginAPI.h
* API for external tools that need to use INS
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "InsPluginAPI.h"

InsWrapper* CreateInsObject(const char* confFilePath) {
    return new InsWrapper(confFilePath);
}

void DeleteInsObject(InsWrapper* pObj) {delete pObj;}

void RunIns(InsWrapper* pObj) { pObj->Run(); }

void SendInsData(InsWrapper* pObj) { pObj->SetData(); }

void SetInsTimeStamps(InsWrapper* pObj, float simTime, float utcTime) {
    pObj->SetTimeStamps(simTime, utcTime);
}

// INS navigation data message
void SetInsPose(InsWrapper* pObj, float latitude, float longitude, float altitude) {
    pObj->SetPose(latitude, longitude, altitude);
}

void SetInsOrientation(InsWrapper* pObj, float azimuth, float pitch, float roll) {
    pObj->SetOrientation(azimuth, pitch, roll);
}

void SetInsAzimuthRate(InsWrapper* pObj, float azimuthRate) { pObj->SetAzimuthRate(azimuthRate); }

void SetInsVelocity(InsWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity) {
    pObj->SetVelocity(northVelocity, eastVelocity, downVelocity);
}

void SetInsDistances(InsWrapper* pObj, float distanceTraveled, float odometerDistance) {
    pObj->SetDistances(distanceTraveled, odometerDistance);
}

void SetInsMotionDetected(InsWrapper* pObj, bool motionDetected) { pObj->SetMotionDetected(motionDetected); }

// INS internal GPS
void SetInsInternalGpsFields(InsWrapper* pObj, short gpsFom, short numOfSatelites) {
    pObj->SetInternalGpsFields(gpsFom, numOfSatelites);
}

// INS Errors estimation message
void SetInsDirectionErrors(InsWrapper* pObj, float horizontalError, float verticalError, float northingError,
                            float eastingError, float altitudeError) {
    pObj->SetDirectionErrors(horizontalError, verticalError, northingError, eastingError, altitudeError);
}

void SetInsVelocityErrors(InsWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError) {
    pObj->SetVelocityErrors(northVelocityError, eastVelocityError, downVelocityError);
}

void SetInsOrientationErrors(InsWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation) {
    pObj->SetOrientationErrors(azimuthErrorEstimation, pitchErrorEstimation, rollErrorEstimation);
}