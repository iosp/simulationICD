

/*
* InsPluginAPI.h
* API for external tools that need to use INS
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "InsPluginAPI.h"
#include "InsWrapper.h"

InsWrapper* InsCreateObject(const char* confFilePath) {
    return new InsWrapper(confFilePath);
}

void InsDeleteObject(InsWrapper* pObj) {
    delete pObj;
}

void InsSendStatusMsgData(InsWrapper* pObj) {
    pObj->SetMsgType(INS_STATUS_MSG);
    pObj->SendData();
}

void InsSendInternalGPSData(InsWrapper* pObj){
    pObj->SetMsgType(INS_INTERNAL_GPS_MSG);
    pObj->SendData();
}

void InsSendNavigationData(InsWrapper* pObj){
    pObj->SetMsgType(INS_NAVIGATION_DATA_MSG);
    pObj->SendData();
}

void InsSendErrorEstimationData(InsWrapper* pObj){
    pObj->SetMsgType(INS_ERRORS_ESTIMATION_MSG);
    pObj->SendData();
}

void InsSetTimeStamps(InsWrapper* pObj, float simTime, float utcTime) {
    pObj->SetTimeStamps(simTime, utcTime);
}

// INS navigation data message
void InsSetPose(InsWrapper* pObj, float latitude, float longitude, float altitude) {
    pObj->SetPose(latitude, longitude, altitude);
}

void InsSetOrientation(InsWrapper* pObj, float azimuth, float pitch, float roll) {
    pObj->SetOrientation(azimuth, pitch, roll);
}

void InsSetAzimuthRate(InsWrapper* pObj, float azimuthRate) {
    pObj->SetAzimuthRate(azimuthRate); 
}

void InsSetVelocity(InsWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity) {
    pObj->SetVelocity(northVelocity, eastVelocity, downVelocity);
}

void InsSetDistances(InsWrapper* pObj, float distanceTraveled, float odometerDistance) {
    pObj->SetDistances(distanceTraveled, odometerDistance);
}

void InsSetMotionDetected(InsWrapper* pObj, bool motionDetected) {
    pObj->SetMotionDetected(motionDetected); 
}

// INS internal GPS
void InsSetInternalGpsFields(InsWrapper* pObj, short gpsFom, short numOfSatelites) {
    pObj->SetInternalGpsFields(gpsFom, numOfSatelites);
}

// INS Errors estimation message
void InsSetDirectionErrors(InsWrapper* pObj, float horizontalError, float verticalError, float northingError,
                            float eastingError, float altitudeError) {
    pObj->SetDirectionErrors(horizontalError, verticalError, northingError, eastingError, altitudeError);
}

void InsSetVelocityErrors(InsWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError) {
    pObj->SetVelocityErrors(northVelocityError, eastVelocityError, downVelocityError);
}

void InsSetOrientationErrors(InsWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation) {
    pObj->SetOrientationErrors(azimuthErrorEstimation, pitchErrorEstimation, rollErrorEstimation);
}