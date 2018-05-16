#ifndef DGPSPLUGINAPI_H
#define DGPSPLUGINAPI_H

/*
* DgpsPluginAPI.h
* API for external tools that need to use DGPS
* Author: Binyamin Appelbaum
* Date: 23.01.18
*/

struct DgpsWrapper;

// Functions that can be used by the plugin
extern "C" {
    DgpsWrapper* DgpsCreateObject(const char* confFilePath);

    void DgpsDeleteObject(DgpsWrapper* pObj);

    void DgpsSendBestPosData(DgpsWrapper* pObj);

    void DgpsSendBestVelData(DgpsWrapper* pObj);

    void DgpsSetPosition(DgpsWrapper* pObj, double latitude, double longitude, double altitude);

    void DgpsSetVelocities(DgpsWrapper* pObj, double latSpeed, double longSpeed, double altAzimuth);

    void DgpsSetTimeStamp(DgpsWrapper* pObj, float timeStamp);
}

#endif // DGPSPLUGINAPI_H