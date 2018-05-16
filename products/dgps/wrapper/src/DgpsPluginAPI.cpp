

/*
* DgpsPluginAPI.h
* API for external tools that need to use DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "DgpsPluginAPI.h"
#include "DgpsWrapper.h"

DgpsWrapper* DgpsCreateObject(const char* confFilePath) {
    return new DgpsWrapper(confFilePath);
}

void DgpsDeleteObject(DgpsWrapper* pObj) {
    delete pObj;
}

void DgpsSendBestPosData(DgpsWrapper* pObj) {
    pObj->SetMsgType(DGPS_BEST_POS);
    pObj->SendData();
}

void DgpsSendBestVelData(DgpsWrapper* pObj) {
    pObj->SetMsgType(DGPS_BEST_VEL);
    pObj->SendData();
}

void DgpsSetPosition(DgpsWrapper* pObj, double latitude, double longitude, double altitude) {
    pObj->SetPosition(latitude, longitude, altitude);
}

void DgpsSetVelocities(DgpsWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth) {
    pObj->SetVelocities(latSpeed, longSpeed, altAzimuth);
}

void DgpsSetTimeStamp(DgpsWrapper* pObj, float timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}