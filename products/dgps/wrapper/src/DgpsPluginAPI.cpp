

/*
* DgpsPluginAPI.h
* API for external tools that need to use DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "DgpsPluginAPI.h"

DgpsWrapper* CreateDgpsObject(const char* confFilePath) {
    return new DgpsWrapper(confFilePath);
}

void DeleteDgpsObject(DgpsWrapper* pObj) {delete pObj;}

void RunDgps(DgpsWrapper* pObj) { pObj->Run(); }

void SendDgpsData(DgpsWrapper* pObj) { pObj->SetData(); }

void SetPosition(DgpsWrapper* pObj, double latitude, double longitude, double altitude) {
    pObj->SetPosition(latitude, longitude, altitude);
}

void SetVelocities(DgpsWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth) {
    pObj->SetVelocities(latSpeed, longSpeed, altAzimuth);
}

void SetDgpsTimeStamp(DgpsWrapper* pObj, float timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}