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

void InsWrapper::Run() {
    m_icd->Run();
}

void InsWrapper::SetData() {
    m_icd->SetData(m_data);
    // ClearCurrentData(); // TODO think about it!
}

void InsWrapper::ClearCurrentData() {
    m_data = InsData();
}

 void InsWrapper::SetTimeStamps(int simTime, int utcTime) {
      m_data.SetSimTime(boost::posix_time::microseconds(simTime));
      m_data.SetUtcTime(boost::posix_time::microseconds(utcTime));
 }

// INS navigation data message
void InsWrapper::SetPose(float altitude, float longitude, float latitude) {
    m_data.SetAltitude(altitude);
    m_data.SetLongitude(longitude);
    m_data.SetLatitude(latitude);
}

void InsWrapper::SetOrientation(float azimuth, float pitch, float roll) {
    m_data.SetAzimuth(azimuth);
    m_data.SetPitch(pitch);
    m_data.SetRoll(roll);
}

void InsWrapper::SetAzimuthRate(float azimuthRate) {
    m_data.SetAzimuthRate(azimuthRate);
}

void InsWrapper::SetVelocity(float northVelocity, float eastVelocity, float downVelocity) {
    m_data.SetNorthVelocity(northVelocity);
    m_data.SetEastVelocity(eastVelocity);
    m_data.SetDownVelocity(downVelocity);
}

void InsWrapper::SetDistances(float distanceTraveled, float odometerDistance) {
    m_data.SetDistanceTraveled(distanceTraveled);
    m_data.SetOdometerDistance(odometerDistance);
}

void InsWrapper::SetMotionDetected(bool motionDetected) {
    m_data.SetMotionDetected(motionDetected);
}

// INS internal GPS
void InsWrapper::SetInternalGpsFields(short gpsFom, short numOfSatelites) {
    m_data.SetGpsFom(gpsFom);
    m_data.SetNumOfSatelites(numOfSatelites);
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