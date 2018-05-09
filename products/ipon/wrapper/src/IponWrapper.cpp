/*
* IponWrapper.cpp
* Wrapper for IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponWrapper.h"
#include "IponControl.h"


IponWrapper::IponWrapper(const std::string& confFilePath) {
    m_icd = new IponControl(confFilePath);
}

IponWrapper::~IponWrapper(){
    delete m_icd;
}

void IponWrapper::Run() {
    m_icd->Run();
}

void IponWrapper::SetData() {
    m_icd->SetData(m_data);
    ClearCurrentData();
}

void IponWrapper::ClearCurrentData() {
    m_data = IponData();
}

void IponWrapper::SetSimTime(float simTime) {
    m_data.SetSimTime(simTime);
}

/************************************************* Periodic 1 HZ ********************************************/
void IponWrapper::Set1HZInsTime(double insTime) {
    m_data.Set1HZInsTime(insTime);
}

void IponWrapper::Set1HZGpsTime(double gpsTime) {
    m_data.Set1HZGpsTime(gpsTime);
}

void IponWrapper::Set1HZLatitude(double latitude) {
    m_data.Set1HZLatitude(latitude);
}

void IponWrapper::Set1HZLongitude(double longitude) {
    m_data.Set1HZLongitude(longitude);
}

void IponWrapper::Set1HZAltitude(double altitude) {
    m_data.Set1HZAltitude(altitude);
}

void IponWrapper::Set1HZWeek(short week) {
    m_data.Set1HZWeek(week);
}

/************************************************* Periodic 100 HZ ********************************************/
void IponWrapper::Set100HZAzimuthGeo(double azimuthGeo) {
	m_data.Set100HZAzimuthGeo(azimuthGeo);
}

void IponWrapper::Set100HZPitch(double pitch) {
	m_data.Set100HZPitch(pitch);
}

void IponWrapper::Set100HZRoll(double roll) {
	m_data.Set100HZRoll(roll);
}

void IponWrapper::Set100HZRollRateX(double rollRateX) {
	m_data.Set100HZRollRateX(rollRateX);
}

void IponWrapper::Set100HZPitchRateY(double pitchRateY) {
	m_data.Set100HZPitchRateY(pitchRateY);
}

void IponWrapper::Set100HZAzimuthRateZ(double azimuthRateZ) {
	m_data.Set100HZAzimuthRateZ(azimuthRateZ);
}

void IponWrapper::Set100HZEccX(double eccX) {
	m_data.Set100HZEccX(eccX);
}

void IponWrapper::Set100HZEccY(double eccY) {
	m_data.Set100HZEccY(eccY);
}

void IponWrapper::Set100HZAltitude(double altitude) {
	m_data.Set100HZAltitude(altitude);
}

void IponWrapper::Set100HZLatitude(double latitude) {
	m_data.Set100HZLatitude(latitude);
}

void IponWrapper::Set100HZLongitude(double longitude) {
	m_data.Set100HZLongitude(longitude);
}

void IponWrapper::Set100HZVelocityEast(double velocityEast) {
	m_data.Set100HZVelocityEast(velocityEast);
}

void IponWrapper::Set100HZVelocityNorth(double velocityNorth) {
	m_data.Set100HZVelocityNorth(velocityNorth);
}

void IponWrapper::Set100HZVelocityDown(double velocityDown) {
	m_data.Set100HZVelocityDown(velocityDown);
}

void IponWrapper::Set100HZInsTimeOfNavData(double insTimeOfNavData) {
	m_data.Set100HZInsTimeOfNavData(insTimeOfNavData);
}

