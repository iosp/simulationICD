/*
* TiltanWrapper.cpp
* Wrapper for Tiltan
* Author: Binyamin Appelbaum
* Date: 18.02.18
*/

#include "TiltanWrapper.h"
#include "TiltanControl.h"


TiltanWrapper::TiltanWrapper(const std::string& confFilePath) {
    m_icd = new TiltanControl(confFilePath);
}

TiltanWrapper::~TiltanWrapper(){
    delete m_icd;
}

void TiltanWrapper::SendData() {
    m_icd->SendData(m_data);
    // ClearCurrentData(); // TODO think about it!
}

void TiltanWrapper::ClearCurrentData() {
    m_data = TiltanData();
}

 void TiltanWrapper::SetTimeStamps(float simTime, float utcTime) {
      m_data.SetSimTime(simTime);
      m_data.SetUtcTime(utcTime);
 }

// Tiltan navigation data message
void TiltanWrapper::SetPose(float latitude, float longitude, float altitude) {
    m_data.SetNavDataAltitude(altitude);
    m_data.SetNavDataLongitude(longitude);
    m_data.SetNavDataLatitude(latitude);
}

void TiltanWrapper::SetOrientation(float azimuth, float pitch, float roll) {
    m_data.SetNavDataAzimuth(azimuth);
    m_data.SetNavDataPitch(pitch);
    m_data.SetNavDataRoll(roll);
}

void TiltanWrapper::SetAzimuthRate(float azimuthRate) {
    m_data.SetNavDataAzimuthRate(azimuthRate);
}

void TiltanWrapper::SetVelocity(float northVelocity, float eastVelocity, float downVelocity) {
    m_data.SetNavDataNorthVelocity(northVelocity);
    m_data.SetNavDataEastVelocity(eastVelocity);
    m_data.SetNavDataDownVelocity(downVelocity);
}

void TiltanWrapper::SetDistances(float distanceTraveled, float odometerDistance) {
    m_data.SetNavDataDistanceTraveled(distanceTraveled);
    m_data.SetNavDataOdometerDistance(odometerDistance);
}

void TiltanWrapper::SetMotionDetected(bool motionDetected) {
    m_data.SetNavDataMotionDetected(motionDetected);
}

// Tiltan internal GPS
void TiltanWrapper::SetInternalGpsFields(short gpsFom, short numOfSatelites) {
    m_data.SetIntGpsGpsFom(gpsFom);
    m_data.SetIntGpsNumOfSatelites(numOfSatelites);
}

// Tiltan Errors estimation message
void TiltanWrapper::SetDirectionErrors(float horizontalError, float verticalError, float northingError, float eastingError, float altitudeError) {
    m_data.SetHorizontalError(horizontalError);
    m_data.SetVerticalError(verticalError);
    m_data.SetNorthingError(northingError);
    m_data.SetEastingError(eastingError);
    m_data.SetAltitudeError(altitudeError);
}

void TiltanWrapper::SetVelocityErrors(float northVelocityError, float eastVelocityError, float downVelocityError) {
    m_data.SetNorthVelocityError(northVelocityError);
    m_data.SetEastVelocityError(eastVelocityError);
    m_data.SetDownVelocityError(downVelocityError);
}

void TiltanWrapper::SetOrientationErrors(float azimuthErrorEstimation, float pitchErrorEstimation, float rollErrorEstimation) {
    m_data.SetAzimuthErrorEstimation(azimuthErrorEstimation);
    m_data.SetPitchErrorEstimation(pitchErrorEstimation);
    m_data.SetRollErrorEstimation(rollErrorEstimation);
}

void TiltanWrapper::SetMsgType(TiltanMsgType msgType) {
    m_data.SetCurrMsgType(msgType);
}