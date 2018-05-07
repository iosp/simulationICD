
/*
* VLPPluginAPI.cpp
* API for external tools that need to use VLP
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VLPPluginAPI.h"

VLPWrapper* VLPCreateObject(const char* confFilePath) {
    return new VLPWrapper(confFilePath);
}

void VLPDeleteObject(VLPWrapper* pObj) {
    delete pObj;
}

void VLPSetAzimuth(VLPWrapper* pObj, double azimuth) {
    pObj->SetAzimuth(azimuth);
}

void VLPSetTimeStamp(VLPWrapper* pObj, float timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}

void VLPSetChannel(VLPWrapper* pObj, double distance, short reflectivity) {
    pObj->SetChannel(distance, reflectivity);
}

void VLPCloseBlock(VLPWrapper* pObj) {
    pObj->CloseBlock();
}

void VLPSendData(VLPWrapper* pObj) {
    pObj->SetData();
}