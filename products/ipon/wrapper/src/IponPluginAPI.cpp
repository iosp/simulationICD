/*
* IponPluginAPI.cpp
* API for external tools that need to use IPON
* Author: Binyamin Appelbaum
* Date: 08.05.18
*/

#include "IponPluginAPI.h"
#include "IponWrapper.h"

IponWrapper* IponCreateObject(const char* confFilePath) {
    return new IponWrapper(confFilePath);
}

void IponDeleteObject(IponWrapper* pObj) {
    delete pObj;
}

void IponSendPeriodic1HZData(IponWrapper* pObj) {
    pObj->SetMsgType(IPON_PERIODIC_1HZ);
	pObj->SendData();
}

void IponSendPeriodic100HZData(IponWrapper* pObj) {
    pObj->SetMsgType(IPON_PERIODIC_100HZ);
	pObj->SendData();
}

void IponSetSimTime(IponWrapper* pObj, float simTime) {
    pObj->SetSimTime(simTime);
}

/************************************************* Periodic 1 HZ ********************************************/
void IponSet1HZInsTime(IponWrapper* pObj, double insTime) {
	pObj->Set1HZInsTime(insTime);
}

void IponSet1HZGpsTime(IponWrapper* pObj, double gpsTime) {
	pObj->Set1HZGpsTime(gpsTime);
}

void IponSet1HZLatitude(IponWrapper* pObj, double latitude) {
	pObj->Set1HZLatitude(latitude);
}

void IponSet1HZLongitude(IponWrapper* pObj, double longitude) {
	pObj->Set1HZLongitude(longitude);
}

void IponSet1HZAltitude(IponWrapper* pObj, double altitude) {
	pObj->Set1HZAltitude(altitude);
}

void IponSet1HZWeek(IponWrapper* pObj, short week) {
	pObj->Set1HZWeek(week);
}

/************************************************* Periodic 100 HZ ********************************************/
void IponSet100HZAzimuthGeo(IponWrapper* pObj, double azimuthGeo) {
	pObj->Set100HZAzimuthGeo(azimuthGeo);
}

void IponSet100HZPitch(IponWrapper* pObj, double pitch) {
	pObj->Set100HZPitch(pitch);
}

void IponSet100HZRoll(IponWrapper* pObj, double roll) {
	pObj->Set100HZRoll(roll);
}

void IponSet100HZRollRateX(IponWrapper* pObj, double rollRateX) {
	pObj->Set100HZRollRateX(rollRateX);
}

void IponSet100HZPitchRateY(IponWrapper* pObj, double pitchRateY) {
	pObj->Set100HZPitchRateY(pitchRateY);
}

void IponSet100HZAzimuthRateZ(IponWrapper* pObj, double azimuthRateZ) {
	pObj->Set100HZAzimuthRateZ(azimuthRateZ);
}

void IponSet100HZEccX(IponWrapper* pObj, double eccX) {
	pObj->Set100HZEccX(eccX);
}

void IponSet100HZEccY(IponWrapper* pObj, double eccY) {
	pObj->Set100HZEccY(eccY);
}

void IponSet100HZAltitude(IponWrapper* pObj, double altitude) {
	pObj->Set100HZAltitude(altitude);
}

void IponSet100HZLatitude(IponWrapper* pObj, double latitude) {
	pObj->Set100HZLatitude(latitude);
}

void IponSet100HZLongitude(IponWrapper* pObj, double longitude) {
	pObj->Set100HZLongitude(longitude);
}

void IponSet100HZVelocityEast(IponWrapper* pObj, double velocityEast) {
	pObj->Set100HZVelocityEast(velocityEast);
}

void IponSet100HZVelocityNorth(IponWrapper* pObj, double velocityNorth) {
	pObj->Set100HZVelocityNorth(velocityNorth);
}

void IponSet100HZVelocityDown(IponWrapper* pObj, double velocityDown) {
	pObj->Set100HZVelocityDown(velocityDown);
}

void IponSet100HZInsTimeOfNavData(IponWrapper* pObj, double insTimeOfNavData) {
	pObj->Set100HZInsTimeOfNavData(insTimeOfNavData);
}
