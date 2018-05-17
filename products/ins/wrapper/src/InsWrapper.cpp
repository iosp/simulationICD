/*
* InsWrapper.cpp
* Wrapper for INS
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "InsWrapper.h"
#include "InsControl.h"


InsWrapper::InsWrapper(const std::string& confFilePath) {
    m_icd = new InsControl(confFilePath);
}

InsWrapper::~InsWrapper(){
    delete m_icd;
}

void InsWrapper::SendData() {
    m_icd->SendData(m_data);
    // ClearCurrentData(); // TODO think about it!
}

void InsWrapper::ClearCurrentData() {
    m_data = InsData();
}

 void InsWrapper::SetTimeStamps(float simTime, float utcTime) {
      m_data.SetSimTime(simTime);
      m_data.SetUtcTime(utcTime);
 }

// INS navigation data message
void InsWrapper::SetPose(float latitude, float longitude, float altitude) {
    m_data.SetNavDataAltitude(altitude);
    m_data.SetNavDataLongitude(longitude);
    m_data.SetNavDataLatitude(latitude);
}

void InsWrapper::SetOrientation(float azimuth, float pitch, float roll) {
    m_data.SetNavDataAzimuth(azimuth);
    m_data.SetNavDataPitch(pitch);
    m_data.SetNavDataRoll(roll);
}

void InsWrapper::SetAzimuthRate(float azimuthRate) {
    m_data.SetNavDataAzimuthRate(azimuthRate);
}

void InsWrapper::SetVelocity(float northVelocity, float eastVelocity, float downVelocity) {
    m_data.SetNavDataNorthVelocity(northVelocity);
    m_data.SetNavDataEastVelocity(eastVelocity);
    m_data.SetNavDataDownVelocity(downVelocity);
}

void InsWrapper::SetDistances(float distanceTraveled, float odometerDistance) {
    m_data.SetNavDataDistanceTraveled(distanceTraveled);
    m_data.SetNavDataOdometerDistance(odometerDistance);
}

void InsWrapper::SetMotionDetected(bool motionDetected) {
    m_data.SetNavDataMotionDetected(motionDetected);
}

// INS internal GPS
void InsWrapper::SetInternalGpsFields(short gpsFom, short numOfSatelites) {
    m_data.SetIntGpsGpsFom(gpsFom);
    m_data.SetIntGpsNumOfSatelites(numOfSatelites);
}

// INS Errors estimation message
void InsWrapper::SetDirectionErrors(float horizontalError, float verticalError, float northingError, float eastingError, float altitudeError) {
    m_data.SetHorizontalError(horizontalError);
    m_data.SetVerticalError(verticalError);
    m_data.SetNorthingError(northingError);
    m_data.SetEastingError(eastingError);
    m_data.SetAltitudeError(altitudeError);
}

void InsWrapper::SetVelocityErrors(float northVelocityError, float eastVelocityError, float downVelocityError) {
    m_data.SetNorthVelocityError(northVelocityError);
    m_data.SetEastVelocityError(eastVelocityError);
    m_data.SetDownVelocityError(downVelocityError);
}

void InsWrapper::SetOrientationErrors(float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation) {
    m_data.SetAzimuthErrorEstimation(azimuthErrorEstimation);
    m_data.SetPitchErrorEstimation(pitchErrorEstimation);
    m_data.SetRollErrorEstimation(rollErrorEstimation);
}

void InsWrapper::SetMsgType(InsMsgType msgType) {
    m_data.SetCurrMsgType(msgType);
}