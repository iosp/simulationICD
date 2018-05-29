/*
* NovatelPluginAPI.h
* API for external tools that need to use Novatel
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

#include "NovatelPluginAPI.h"
#include "NovatelWrapper.h"

NovatelWrapper* NovatelCreateObject(const char* confFilePath) {
    return new NovatelWrapper(confFilePath);
}

void NovatelDeleteObject(NovatelWrapper* pObj) {
    delete pObj;
}

void NovatelInitCommunication(NovatelWrapper* pObj) {
    pObj->InitCommunication();
}

void NovatelSendBestPosData(NovatelWrapper* pObj) {
    pObj->SetMsgType(NOVATEL_BEST_POS);
    pObj->SendData();
}

void NovatelSendBestVelData(NovatelWrapper* pObj) {
    pObj->SetMsgType(NOVATEL_BEST_VEL);
    pObj->SendData();
}

void NovatelSetPosition(NovatelWrapper* pObj, double latitude, double longitude, double altitude) {
    pObj->SetPosition(latitude, longitude, altitude);
}

void NovatelSetVelocities(NovatelWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth) {
    pObj->SetVelocities(latSpeed, longSpeed, altAzimuth);
}

void NovatelSetTimeStamp(NovatelWrapper* pObj, float timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}