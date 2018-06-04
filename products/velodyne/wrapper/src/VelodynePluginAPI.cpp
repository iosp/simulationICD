/*
* VelodynePluginAPI.cpp
* API for external tools that need to use Velodyne
* Author: Binyamin Appelbaum
* Date: 04.01.18
*/

#include "VelodynePluginAPI.h"
#include "VelodyneWrapper.h"

VelodyneWrapper* VelodyneCreateObject(const char* confFilePath) {
    return new VelodyneWrapper(confFilePath);
}

void VelodyneDeleteObject(VelodyneWrapper* pObj) {
    delete pObj;
}

void VelodyneSetAzimuth(VelodyneWrapper* pObj, double azimuth) {
    pObj->SetAzimuth(azimuth);
}

void VelodyneSetTimeStamp(VelodyneWrapper* pObj, float timeStamp) {
    pObj->SetTimeStamp(timeStamp);
}

void VelodyneSetChannel(VelodyneWrapper* pObj, double distance, short reflectivity) {
    pObj->SetChannel(distance, reflectivity);
}

void VelodyneCloseBlock(VelodyneWrapper* pObj) {
    pObj->CloseBlock();
}

void VelodyneSendData(VelodyneWrapper* pObj) {
    pObj->SendData();
}