/*
* TiltanPluginAPI.h
* API for external tools that need to use Tiltan
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "TiltanPluginAPI.h"
#include "TiltanWrapper.h"

TiltanWrapper* TiltanCreateObject(const char* confFilePath) {
    return new TiltanWrapper(confFilePath);
}

void TiltanDeleteObject(TiltanWrapper* pObj) {
    delete pObj;
}

void TiltanSendStatusMsgData(TiltanWrapper* pObj) {
    pObj->SetMsgType(TILTAN_STATUS_MSG);
    pObj->SendData();
}

void TiltanSendInternalGPSData(TiltanWrapper* pObj){
    pObj->SetMsgType(TILTAN_INTERNAL_GPS_MSG);
    pObj->SendData();
}

void TiltanSendNavigationData(TiltanWrapper* pObj){
    pObj->SetMsgType(TILTAN_NAVIGATION_DATA_MSG);
    pObj->SendData();
}

void TiltanSendErrorEstimationData(TiltanWrapper* pObj){
    pObj->SetMsgType(TILTAN_ERRORS_ESTIMATION_MSG);
    pObj->SendData();
}

void TiltanSetTimeStamps(TiltanWrapper* pObj, float simTime, float utcTime) {
    pObj->SetTimeStamps(simTime, utcTime);
}

// Tiltan navigation data message
void TiltanSetPose(TiltanWrapper* pObj, float latitude, float longitude, float altitude) {
    pObj->SetPose(latitude, longitude, altitude);
}

void TiltanSetOrientation(TiltanWrapper* pObj, float azimuth, float pitch, float roll) {
    pObj->SetOrientation(azimuth, pitch, roll);
}

void TiltanSetAzimuthRate(TiltanWrapper* pObj, float azimuthRate) {
    pObj->SetAzimuthRate(azimuthRate); 
}

void TiltanSetVelocity(TiltanWrapper* pObj, float northVelocity, float eastVelocity, float downVelocity) {
    pObj->SetVelocity(northVelocity, eastVelocity, downVelocity);
}

void TiltanSetDistances(TiltanWrapper* pObj, float distanceTraveled, float odometerDistance) {
    pObj->SetDistances(distanceTraveled, odometerDistance);
}

void TiltanSetMotionDetected(TiltanWrapper* pObj, bool motionDetected) {
    pObj->SetMotionDetected(motionDetected); 
}

// Tiltan internal GPS
void TiltanSetInternalGpsFields(TiltanWrapper* pObj, short gpsFom, short numOfSatelites) {
    pObj->SetInternalGpsFields(gpsFom, numOfSatelites);
}

// Tiltan Errors estimation message
void TiltanSetDirectionErrors(TiltanWrapper* pObj, float horizontalError, float verticalError, float northingError,
                            float eastingError, float altitudeError) {
    pObj->SetDirectionErrors(horizontalError, verticalError, northingError, eastingError, altitudeError);
}

void TiltanSetVelocityErrors(TiltanWrapper* pObj, float northVelocityError, float eastVelocityError, float downVelocityError) {
    pObj->SetVelocityErrors(northVelocityError, eastVelocityError, downVelocityError);
}

void TiltanSetOrientationErrors(TiltanWrapper* pObj, float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation) {
    pObj->SetOrientationErrors(azimuthErrorEstimation, pitchErrorEstimation, rollErrorEstimation);
}